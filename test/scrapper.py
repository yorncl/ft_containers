from bs4 import BeautifulSoup as bs
import urllib.request as rq
import errno, os
import config


# get containers page
def getWebpages():
    try:
        os.makedirs(config.pagesDir)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise
    for name in config.containers:
        #container dir names
        containerDir = config.pagesDir + '/' + name
        functionsDir = containerDir + '/functions'
        #make the dirs
        try:
            os.makedirs(functionsDir)
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise
        
        #getting main html page
        filename = 'pages/' + name + '/' + name +  '.html'

        #if not exist download it
        print("==> Getting documentation for:   " + name)
        if not os.path.exists(filename):
            with open(filename, 'w') as f: 
                page = rq.urlopen(config.baseUrl + '/reference' + '/' + name + '/' + name)
                soup = bs(page, 'html.parser')
                #writing main html page
                f.write(str(soup))
                print("\tDownloaded " + name)

        with open(filename, 'r') as f: 
            soup = bs(f.read(), 'html.parser')
            links = soup.select("#functions")[0].select("a")
            links[:] = [x for x in links if not x.select(".C_cpp11") ]
            for l in links:
                label = list([x for x in l['href'].split('/') if x])[-1]
                #skipping get_allocator as subjects says
                if label == "get_allocator":
                    continue
                #converting special labels
                if label == "(constructor)":
                    label = name
                if label == "(destructor)":
                    label = '~' + name
                functionfile = functionsDir + '/' + label + '.html'
                if not os.path.exists(functionfile):
                    #query that url
                    page = rq.urlopen(config.baseUrl + l['href'])
                    #writing the result to the file
                    soup = bs(page, 'html.parser')
                    with open(functionfile, 'w') as ff:
                        ff.write(str(soup))
                    print("\tDownloaded " + label)

if __name__ == "__main__":
    getWebpages()
