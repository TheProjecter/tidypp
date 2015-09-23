You can get curlplusplus [here](http://code.google.com/p/curlplusplus).

```
#include <tidypp/document.hpp>
#include <tidypp/attribute.hpp>
#include <tidypp/buffer.hpp>
#include <tidypp/node.hpp>
#include <curlplusplus/easy.hpp>
#include <string>
#include <list>
#include <iostream>

void dumphrefs(tidypp::node &node, std::list<std::string> *dst);
static int writer(char *data, size_t size, size_t nmemb, tidypp::buffer *dst);

int main(int argc, char *argv[])
{
    std::list<std::string> links; // will store the link list
    tidypp::document doc; // tidy html document
    tidypp::buffer html; // will store our html code
    tidypp::buffer errbuf; // will store the warnings and errors encountered by html tidy
    tidypp::node root; // will store the root node of the document

    // make sure the link is provided in the command line args
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
        return 1;
    }

    // obtain the page's html via cURL
    try
    {
        curlpp::easy curl; // handle to the curl easy interface
        long http_status; // will store the result of the curl request

        std::cout << "Obtaining page..." << std::endl;
        curl.setopt(CURLOPT_URL, argv[1]); // assign URL
        curl.setopt(CURLOPT_FOLLOWLOCATION, 1);
        curl.setopt(CURLOPT_WRITEFUNCTION, writer); // assign write callback
        curl.setopt(CURLOPT_WRITEDATA, &html); // assign write buffer (our tidypp buffer)
        curl.perform(); // perform curl
        curl.getinfo(CURLINFO_RESPONSE_CODE, &http_status); // get result http status

        if (http_status != 200)
        {
            std::cerr << "Expecting HTTP 200 OK, got " << http_status << std::endl;
            return 1;
        }
    }
    catch (const curlpp::exception &e) // catch exceptions and print the error on screen
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // parse the page
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

    std::cout << "Found " << links.size() << " links:" << std::endl;

    // iterate the links list
    for (std::list<std::string>::iterator it = links.begin(); it != links.end(); it++)
        std::cout << *it << std::endl;

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

/**
 * Write callback called by cURL every time it obtains some data.
 *
 * @param[in] data the data that has just been obtained.
 * @param size the size of each data block.
 * @param nmemb the number of data blocks. multiply this by size to obtain the
 *              total size of data.
 * @param[out] dst the destination buffer that was assigned to CURLOPT_WRITEDATA
 *
 * @return the amount of bytes that were dispatched to the destination buffer.
 */
static int writer(char *data, size_t size, size_t nmemb, tidypp::buffer *dst)
{
    size_t len;

    if (!data)
        return 0;

    len = size * nmemb;
    dst->append(data, len); // append recieved data to the buffer

    return len; // must return the amount of written bytes
}
```