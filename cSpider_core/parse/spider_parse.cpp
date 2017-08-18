/*************************************************************************
	> File Name: spider_parse.cpp
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年08月18日 星期五 16时09分14秒
 ************************************************************************/

#include <iostream>
#include <spider_parse.h>
#include <../../lib/htmlcxx/html/ParserDom.h>
#include <string>
#include <../io/spider_io.h>

using namespace std;
using namespace CSpider::IO;
using namespace htmlcxx;
using namespace CSpider::Parse;

SpiderParse::SpiderParse() {

}

SpiderParse::~SpiderParse() {

}

void SpiderParse::parse_html(std::string& page) {

    string      html;
    SpiderIO    io;

    io.io_read("blog.csdn.net/html/grandPang_article_details_47448395", html);
    HTML::ParserDom parse;

    tree<HTML::Node> dom = parse.parseTree(html);

    //cout << dom << endl;
    tree<HTML::Node>::iterator it = dom.begin();
    tree<HTML::Node>::iterator end = dom.end();

    /*
    for(; it != end; ++ it) {
        if(strcasecmp(it->tagName().c_str(), "A") == 0) {
            it->parseAttributes();
            cout << it->attribute("href").second << endl;
        }
    }
    */

    // 输出所有的文本节点
    it = dom.begin();
    end = dom.end();
    for(; it != end; ++it) {

        if(strcasecmp(it->tagName().c_str(), "script")) {
            continue;
        }

        if((!it->isTag()) && (!it->isComment())) {
            cout << it->text();
        }
    }


    //cout << html << endl;


}

