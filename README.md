# 자료구조론
  
Stack, Queue, Tree 등등 자료구조와 관련된 코드들을 모아놓았습니다.
  
# 환경 세팅
  
C or C++  
ubuntu 20.04.6 LTS  
gcc 6.3.0  

# 실행 방법(wsl내에서 해주세요)
  
1. 원하는 폴더 위치로 이동  
    cd folderPath  
  
2. 컴파일해서 실행파일(myProject) 만들기  
    - C파일  
        gcc -o myProject myProject.c  
    - C++파일  
        g++ -o myProject myProject.cc  
  
3. 실행하기  
    - 출력창 터미널에 출력  
        ./myProject inputFile.txt  
    - 출력내용 txt로 만들기  
        ./myProject inputFile.txt >> outputFile.txt  
  
4. 내용 비교하기  
    - 기본  
        diff output1.txt output2.txt  
    - 차이점 좀 더 자세히  
        diff -u output1.txt output2.txt  
    - 공백 무시  
        diff -w output1.txt output2.txt  
    - 차이점 생략  
        diff -q output1.txt output2.txt  

_부록_  
  
C는 stack이나 queue를 따로 제공하지 않기에 직접 구현해야됩니다.  
하지만 C++은 라이브러리로 이를 제공하고 있습니다.  
너무나 편리하고 도움이 되는 기능이네요  
C++ 만세!!