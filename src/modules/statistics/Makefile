CXX     = c++
LINK    = c++
WEBROOT = /server/web/tgeppert/statistics
OBJECTS = StatisticsWeb.o
INCPATH = -I /usr/local/include -I /usr/include -I /usr/local/include/mysql
LIBPATH = -L /usr/local/lib -L /usr/lib
LIBS    = -l fcgi -lds

TARGET  = index.ds

all: $(TARGET)

install: all
	service apache24 stop
	cp -f $(TARGET) $(WEBROOT)/index.ds
	cp -Rf templates $(WEBROOT)/
	chown -R www:www $(WEBROOT)
	cp -f wpstatistics.conf /usr/local/etc/wpstatistics.conf
	chown -R www:www /usr/local/etc/wpstatistics.conf
	service apache24 start

clean:
	rm -rf $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK) $(LIBPATH) $(LIBS) -O2 -o $(TARGET) $(OBJECTS) `wx-config --libs`

.cpp.o:
	$(CXX) $(INCPATH) -O2 -fPIC -Wall -c $*.cpp -o $*.o `wx-config --cppflags`
