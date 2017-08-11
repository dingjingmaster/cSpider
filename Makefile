CPP = g++

head = -I ./cSpider_core/\
			 -I ./cSpider_core/io/\
			 -I ./cSpider_core/route/\
			 -I ./cSpider_core/downloader/\



# 测试文件目录
mkdir = mkdir
test_file = test
# http_test
http_test = test/http_test
http_test_obj = cSpider_core/downloader/test/http_test.o

# io_test
io_test=test/io_test
io_test_obj = cSpider_core/io/test/io_test.o



.PHONY : all
all:$(mkdir)
	make test


# 最终生成的库文件
cSpider:



# test file
$(mkdir):
	test -d $(test_file) || mkdir $(test_file)


# 测试
.PHONY:test 

test:$(http_test) $(io_test) 


# 测试文件
$(http_test):$(http_test_obj)
	$(CPP) -o $@ $^

$(io_test):$(io_test_obj)
	$(CPP) -o $@ $^

%.o:%.cpp
	$(CPP) -o $@ -c $< $(head)



.PHONY:clean

clean:
	rm -fr $(test_file)
	rm -fr $(io_test)
	rm -fr $(http_test)
	rm -fr $(io_test_obj)
	rm -fr $(http_test_obj)
