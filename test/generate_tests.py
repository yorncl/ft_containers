import config
from bs4 import BeautifulSoup as bs
import os


def createTests():
    for c in config.containers :
        os.makedirs(config.testsDir + '/' + c + '/src', exist_ok=True)
        for file in os.scandir(config.pagesDir + '/' + c + '/functions/' ):
             with open(file, "r") as f :
                 content = f.read()
                 soup = bs(content, 'html.parser')
                 example = soup.find_all(id="example")
                 if len(example) == 1:
                    code = example[0].find(class_="source").find("code").text
                    with open(config.testsDir + '/' + c + '/src/' + file.name.replace(".html", ".cpp"), "w") as testfile:
                        code = code.replace("<" + c +">", "HEADER_FILE")
                        code = code.replace("std::" + c, "NAMESPACE::" + c)
                        testfile.write(code)
                        print("Generated code for " + testfile.name)


if __name__ == "__main__":
    createTests()
