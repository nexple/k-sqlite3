3508라인까지 번역 2014/1/30

sqlite3.c
1라인부터
define
type define
sqlite api 정의
5000라인부터 구조체 나옴.
5307
struct sqlite3_module {

뮤텍스 설명
6189 데이터베이스 상태 설명
6664 캐시 오브젝트
7331 라인 뭔가 끝남.
7486
맥시멈 정하기 테이블수 컬럼 인덱스등
7987 해시
10938 index 시작
12664 lemon 파서(문법 분석기) 시작
11117
expr struct(중요한듯)

13875
vbde(버추얼 데이터 베이스 엔진 ) struct 시작
19000�
메모리
21000
utf8
21529
tcl(에러 맨날 난다고 테스트부분이다.)
23171
opcode 리스트
24361
vxworks
31000
윈도우즈 컴파일관련
33378
윈 ce 특별코드
38000
cache 관련
39949
pager
53908
트랜잭션
59073
백업
66360
버추얼 데이터 베이스 엔진 설명
67122
opcode관련 switch 시작.opcode 실행
68984
 OP_MakeRecord:
70000라인 
opcode 실행부분(레지스터에 들어가는 코드)
81454 
analyze

컨트롤+f 누르고 algorithm 치면 알고리즘(algorithm)이 무척 많이 나옴.
자료구조(structure),테이블(table) 다 조사해서 개선할것.

shell.c



441 콜백 함수(통신응답)
703 쉘 콜백
909 셋 테이블
998 테이블 
1407 덤프 테이블
1542 도움말 
1800 csv 리더기 


