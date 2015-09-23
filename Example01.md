
```
#include <tidypp/document.hpp>
#include <tidypp/attribute.hpp>
#include <tidypp/buffer.hpp>
#include <tidypp/node.hpp>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

void dumphrefs(tidypp::node &node, std::list<std::string> *dst);

int main(int argc, char *argv[])
{
    std::ostringstream oss; // will be used to construct the test html code string
    std::list<std::string> links; // will store the link list
    tidypp::document doc; // tidy html document
    tidypp::buffer html; // will store our html code
    tidypp::buffer errbuf; // will store the warnings and errors encountered by html tidy
    tidypp::node root; // will store the root node of the document

    // let's build some html code, you can obviously replace this with opening an html file or
    // sending an http request with cURL to obtain a page.
    oss << "<!DOCTYPE html>" << std::endl
        << "<html>" << std::endl
        << "<body>" << std::endl
        << "<h1>Example HTML</h1>" << std::endl
        << "<p>" << std::endl
        << "Search Engines:" << std::endl
        << "<a href=\"http://www.google.com\">Google</a>" << std::endl
        << "<a href=\"http://www.bing.com\">Bing</a>" << std::endl
        << "<a href=\"http://search.yahoo.com\">Yahoo</a>" << std::endl
        << "* If all goes well, the above links should be extracted." << std::endl
        << "</p>" << std::endl
        << "</body>" << std::endl
        << "</html>";

    // let's append our html code to our buffer
    html.append(const_cast<char *>(oss.str().c_str()), oss.str().length() + 1); // +1 because of the endstring character

    try
    {
        doc.seterrorbuffer(errbuf); // assign error buffer
        doc.optsetbool(TidyForceOutput, true); // output document even if errors were found
        doc.optsetint(TidyWrapLen, 4096); // wrap margin
        doc.parsebuffer(html); // parse the html in our buffer
        doc.cleanandrepair(); // cleans up and repairs errors
    }
    catch (const tidypp::exception &e) // catch exceptions and print the error on screen
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    root = doc.root(); // get root node
    dumphrefs(root, &links); // dump links to our list

    // if the list is empty...
    if (!links.size())
    {
        std::cerr << "No links found!" << std::endl;
        return 1;
    }

    std::cout << "HTML Code:" << std::endl;
    std::cout << oss.str() << std::endl << std::endl;
    std::cout << "Found " << links.size() << " links:" << std::endl;

    // iterate the links list
    for (std::list<std::string>::iterator it = links.begin(); it != links.end(); it++)
        std::cout << *it << std::endl;

    std::cin.get(); // decent alternative to system pause

    // note: the error buffer is never used in this example, but it's important to set it because
    // tidy html would dump all the errors in stdout otherwise.

    return 0;
}

/**
 * Dumps all the links in the document into an std::list<std::string>
 * by walking the document tree of a tidy html document.
 *
 * @param[in] node the root node of the document.
 * @param[out] dst the destination array of strings.
 */
void dumphrefs(tidypp::node &node, std::list<std::string> *dst)
{
    // iterate all children nodes
    for (tidypp::node child = node.child(); child.valid(); child = child.next())
    {
        tidypp::tagid id = node.id(); // obtain tag id to check if it's a link

        // if the node is an <a> tag...
        if (id == TidyTag_A)
        {
            tidypp::attribute href = node.attrgetbyid(TidyAttr_HREF); // get the href attribute
            ctmbstr hrefval = href.value(); // get the value of the attribute (string of the actual link)

            if (hrefval) // if the link is not empty...
            {
                std::string link(hrefval); // convert to std::string
                dst->push_back(link); // append link to the list
            }
        }

        // walk all the children of each children recursively
        dumphrefs(child, dst);
    }
}
```