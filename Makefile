CPP = g++

head = -I ./cSpider_core/\
			 -I ./cSpider_core/io/\
			 -I ./cSpider_core/route/\
			 -I ./cSpider_core/downloader/\



# http_test
http_test=http_test
http_test_src = ./cSpider_core/downloader/test/http_test.o

# 测试
.PHONY:test

test:$(http_test)

# 最终生成的库文件
cSpider:

# 测试文件
$(http_test):$(http_test_src)
	$(CPP) -o $@ $^


%.o:%.cpp
	$(CPP) -o $@ -c $< $(head)


.PHONY:clean

clean:
	rm -fr $(http_test_src)
	rm -fr $(http_test)
