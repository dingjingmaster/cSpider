CPP = g++

htmlcxx_path = lib/htmlcxx/

htmlcxx = -I $(lib_path)\
					-I $(lib_path)/html/\
					-I $(lib_path)/css/

htmlcxx_obj = $(htmlcxx_path)/html/ParserDom.o\
							$(htmlcxx_path)/html/Node.o\
							$(htmlcxx_path)/html/ParserSax.o

head = -I cSpider_core/\
			 -I cSpider_core/io/\
			 -I cSpider_core/main/\
			 -I cSpider_core/error/\
			 -I cSpider_core/route/\
			 -I cSpider_core/parse/\
			 -I cSpider_core/download/\


src_obj = cSpider_core/io/spider_io.o\
				  cSpider_core/route/spider_route.o\
				  cSpider_core/download/spider_http.o\
					cSpider_core/download/spider_download.o\
					cSpider_core/parse/spider_parse.o




# 测试文件目录
mkdir = mkdir
test_file = test

# http_test
http_test = test/http_test
http_test_obj = cSpider_core/download/test/http_test.o

# io_test
io_test = test/io_test
io_test_obj = cSpider_core/io/test/io_test.o

# route_test
route_test = test/route_test
route_test_obj = cSpider_core/route/test/route_test.o

# download_test
download_test = test/download_test
download_test_obj = cSpider_core/download/test/download_test.o

# 最终生成程序主入口
spider_main = spider_main
spider_main_obj = cSpider_core/main/spider_main.o



# 主文件
target:$(spider_main)



.PHONY : all

all:$(spider_main) 
	make test



# test file
$(mkdir):
	test -d $(test_file) || mkdir $(test_file)


# 测试
.PHONY:test 

test:$(mkdir) $(http_test) $(io_test) $(route_test) $(download_test)


# 测试文件
$(http_test):$(http_test_obj) $(src_obj)
	$(CPP) -o $@ $^

$(download_test):$(download_test_obj) $(src_obj)
	$(CPP) -o $@ $^

$(io_test):$(io_test_obj) $(src_obj)
	$(CPP) -o $@ $^

$(route_test):$(route_test_obj) $(src_obj)
	$(CPP) -o $@ $^








# 最终目标
$(spider_main):$(spider_main_obj) $(src_obj) $(htmlcxx_obj)
	$(CPP) -o $@ $^ 






%.o:%.cpp
	$(CPP) -o $@ -c $< $(head) 


%.o:%.cc
	$(CPP) -o $@ -c $< $(head) 




.PHONY:clean

clean:
	rm -fr $(test_file)
	rm -fr $(spider_main)
	rm -fr $(io_test_obj)
	rm -fr $(http_test_obj)
	rm -fr $(route_test_obj)
	rm -fr $(spider_main_obj)
	rm -fr $(download_test_obj)
	rm -fr $(src_obj)
	rm -fr $(htmlcxx_obj)










