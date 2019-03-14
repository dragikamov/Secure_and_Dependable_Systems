Secure and Dependable Systems
Homework 1
Dragi Kamov


1. After you have unzipped the file go out of it and type in the terminal 'mkdir build'
2. Enter the created folder with 'cd build'
3. Type 'cmake ../HW1'
4. Type 'make'
5. And then there should be an executable 'main' in the HW1 folder which would run the 
   rpnc calculator like instructed in the assignment sheet
6. The html files could be developped if we type 
   'lcov --capture --directory . --output-file cov.info' while we are in the build 
   folder and then 'genhtml cov.info -o html'. Then there should have been created 
   a folder called 'html' and in it are all the statistics