from bs4 import BeautifulSoup as bs 
import re
import os
import errno
import config

def getSoup(c, function = ""):
    soup = None
    path = None
    if function == "":
        path = c + '/' + c + '.html'
    else:
        path = c + '/functions/' + function + '.html' 
    with open(config.pagesDir + '/' + path, 'r') as f:
            page = f.read()
            soup = bs(page, 'html.parser')
    return soup

def writeMemberTypes(soup):
    buff = ""
    buff += "\t\t//Member types\n"
    print("\n\n")
    typename = soup.select('#types div[title="C++98"] table td:nth-child(1) tt')
    typedef = soup.select('#types div[title="C++98"] table td:nth-child(2) tt')
    for i in range(len(typename)):
        line = "\t\t"
        # Added the try catch cause map wasn't working properly
        try :
            tdef = typedef[i].string
        except IndexError:
            tdef = "// TO COMPLETE"
        tname = typename[i].string
        if tdef is not None and not re.search("iterator", tname):
            m = re.search("^(iterator_traits<iterator>::difference_type)", tdef)
            if  m:
                tdef = "std::ptrdiff_t" 
            if len(tdef.split("::")) > 1:
                tdef = "typename " + tdef

        else:
            tdef = "T"
        line += "typedef " + tdef + " " + (tname if tname is not None else "MISSING_NAME") + ";"
        line += "\n"
        buff += line
    return buff

def writeFunctionBody(prototype):
    buff = "{\n"
    
    # print(prototype)
    m = re.search(re.compile("[^()]+\((.*)\)"), prototype)
    if m:
        args = ''.join(m.groups(1)).strip().split(", ")
        if len(args[0]) > 0:
            for arg in args:
                m = re.search("(const )?[A-Za-z0-9_]+(<([A-Za-z0-9_]* ?[A-Za-z0-9_]*,?)*>)?&? ([A-Za-z0-9_]+)", arg)
                if m and m.group(4):
                    buff += "\t\t\t(void) " + m.group(4) + ";\n"
        buff += "\t\t"
    buff += "}"
    # time.sleep(1)
    return buff

def writeFunctions(prototypes):
    buff = ""
    for p in prototypes:
        lines = p.string.strip().split('\n')
        for index, line in enumerate(lines):
            # if the line is not finished, join it to the next one and continue 
            if line[-1] == ',':
                lines[index + 1] = line + " " + lines[index + 1].strip()
                continue
            line = line.strip()
            if re.search("^template *<[A-Za-z0-9 ,]+>$", line):
                buff += "\t\t" + line + "\n"
            elif line[-1] != ";":
                buff += "\t\t" + line + "\n"
            else:
                buff += "\t\t" + line[:-1] + "\n\t\t" + writeFunctionBody(line) + "\n"
    return buff;

def writeMemberFunction(c, fn):
    
    buff = ""
    soup = getSoup(c, fn)
    prototypes = soup.select('.C_prototype div[title="C++98"] pre')
    if not prototypes:
        prototypes = soup.select('.C_prototype pre')
    #comment for section
    buff += "\n\t\t// " + ("constructor" if fn == c else ( "destructor" if ('~' + fn) == c else fn)) + "\n"
    buff += writeFunctions(prototypes)
    # time.sleep(5)
    return buff

def writeFriend(c, fn):
    buff = ""
    soup = getSoup(c, fn)
    prototypes = soup.select('.C_prototype div[title="C++98"] pre')
    if not prototypes:
        prototypes = soup.select('.C_prototype pre')

    if fn == "swap":
        print(prototypes)
    buff += writeFunctions(prototypes)
    return buff

#Class wrapper
def writeHeader(c):
    buff = ""
    soup = getSoup(c)
    template = soup.select(".C_prototype")[0].string
    # if define header wraper
    buff += "#ifndef FT_" + c.upper() + "_HPP\n"
    buff += "#define FT_" + c.upper() + "_HPP\n"
    #includes
    #used for std::alocator
    buff += "#include <memory>"
    buff += "\nnamespace ft\n{\n"
    # The miuns one here is to remove the ; at the end
    buff += '\t' + template[:-1].replace(" = allocator", " = std::allocator") + "\n\t{\n"
    buff += "\t\tprivate:\n"
    buff += writeMemberTypes(soup)
    
    friends = []
    buff += "\t\tpublic:\n"
    # Writing functions
    links = soup.select("#functions")[0].select("a")
    links[:] = [x for x in links if not x.select(".C_cpp11") ]
    for l in links:
        fn = list([x for x in l['href'].split('/') if x])[-1]
        #skipping get_allocator as subjects says
        if fn == "get_allocator":
            continue
        #converting special fns
        if fn == "(constructor)":
            fn = c
        if fn == "(destructor)":
            fn = '~' + c
        if l.string.split()[-1] == "(" + c + ")":
            friends.append(fn)
        else:
            buff += writeMemberFunction(c, fn)
    # end of class
    buff += "\t};\n" 
    #writing non member funcitons

    for f in friends: 
        buff += writeFriend(c, f)
    #end of namespace
    buff += "};\n\n"
    buff += "#endif //" + c.upper() + "_HPP"
    return buff

#making headers
def createHeaders():
    #for each of the containers
    print ("==> Creating headers")
    try:
        os.makedirs(config.headersDir)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise
    for c in config.containers:
        print ("\tcreating " + c + ".hpp")
        
        content = writeHeader(c)
        with open(config.headersDir + "/" + c + ".hpp", 'w') as f:
            f.write(content)

if __name__ == "__main__":
    createHeaders()
