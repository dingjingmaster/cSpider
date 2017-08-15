CPP = g++

head = -I cSpider_core/\
			 -I cSpider_core/io/\
			 -I cSpider_core/main/\
			 -I cSpider_core/http/\
			 -I cSpider_core/error/\
			 -I cSpider_core/route/\

src_obj = cSpider_core/io/spider_io.o\
					cSpider_core/http/spider_http.o\
				  cSpider_core/route/spider_route.o



# 测试文件目录
mkdir = mkdir
test_file = test

# http_test
http_test = test/http_test
http_test_obj = cSpider_core/http/test/http_test.o

# io_test
io_test = test/io_test
io_test_obj = cSpider_core/io/test/io_test.o

# route_test
route_test = test/route_test
route_test_obj = cSpider_core/route/test/route_test.o

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

test:$(mkdir) $(http_test) $(io_test) $(route_test) 


# 测试文件
$(http_test):$(http_test_obj) $(src_obj)
	$(CPP) -o $@ $^

$(io_test):$(io_test_obj) $(src_obj)
	$(CPP) -o $@ $^

$(route_test):$(route_test_obj) $(src_obj)
	$(CPP) -o $@ $^

# 最终目标
$(spider_main):$(spider_main_obj) $(src_obj)
	$(CPP) -o $@ $^






%.o:%.cpp
	$(CPP) -o $@ -c $< $(head)



.PHONY:clean

clean:
	rm -fr $(test_file)
	rm -fr $(spider_main)
	rm -fr $(io_test_obj)
	rm -fr $(http_test_obj)
	rm -fr $(route_test_obj)
	rm -fr $(spider_main_obj)
	rm -fr $(src_obj)










