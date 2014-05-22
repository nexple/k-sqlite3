/*
** 2001 September 15
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** 이 헤더 파일 에는 인터페이스를 정의하고 그 SQLite 라이브러리
** 클라이언트 프로그램 에 제시한다. 만약 C 함수 , 구조 , 데이터 형식,
** 와 정수의 정의는 이 파일 에 표시 되지 않습니다 , ​​그것은이다
** SQLite는 공표 API는 예고 없이 변경 될 수 없습니다
** 깨달아, 그리고 SQLite 를 사용하는 프로그램이 참조 되어야 아니다.
**
** 이 파일 에 포함 된 정의 의 일부는 다음과 같이 표시 된다
** " 실험 " 실험 의 인터페이스 는 일반적으로 새로 추가 된
** 최근 SQLite 에 추가 합니다 . 우리는 변화를 선점 하지 않습니다
** 실험 인터페이스에는없고 약간의 변경 권한을 보유
** " 야생에서 " 사용 경험 이 이러한 변경 이 좋습니다 제안 합니다.
**
** SQLite 에 대한 공식적인 C 언어 의 API 문서 가 도출된다
** 이 파일의 주석 에서 . 이 파일은 신뢰할 수있는 소스 이다
** SQLite 의 인터페이스 가 작동 하도록 하고있다 방법 .
**
** 구성 관리 에 이 파일 의 이름은 " sqlite.h.in " 입니다.
** 메이크업은 삽입 등 이 파일 에 몇 가지 사소한 변경 ( 합니다
** 버전 번호 ) 는 같은 " sqlite3.h "로 회사 명 변경
** 빌드 프로세스 의 일부입니다.
* /
#ifndef _SQLITE3_H_
#define _SQLITE3_H_
#include <stdarg.h>     /* Needed for the definition of va_list */

/*
** Make sure we can call this stuff from C++.
*/
#ifdef __cplusplus
extern "C" {
#endif


/*
** Add the ability to override 'extern'
*/
#ifndef SQLITE_EXTERN
# define SQLITE_EXTERN extern
#endif

#ifndef SQLITE_API
# define SQLITE_API
#endif


/ * 
**이 무 조작 매크로는 그들을 표시하는 인터페이스의 전에 사용 된 
** 인터페이스 비추천 또는 실험 중 하나로서. 새로운 응용 프로그램 
** 비추천의 인터페이스를 사용해서는 안된다 - 그들은 후방 지원이다 
** 호환 만. 어플리케이션의 작성자는 유의해야합니다 
** 실험 인터페이스는 포인트 릴리스에서 변경 될 수 있습니다. 
** 
**이 매크로는 컴파일러 마법의 다양한 종류를 해결하기 위해 사용할 수 
그들을 사용하는 경우 ** 경고 메시지를 생성합니다. 그러나 그 
** 컴파일러의 마법 버그 리포트와 같은 돌풍을 발생 시키게되었다 
** 우리는 그것을 전부 제거하고 간단한 사용을 맞댄했다는 것을 
** NOOP 매크로. 
* /
#define SQLITE_DEPRECATED
#define SQLITE_EXPERIMENTAL

/*
** Ensure these symbols were not defined by some previous header file.
*/
#ifdef SQLITE_VERSION
# undef SQLITE_VERSION
#endif
#ifdef SQLITE_VERSION_NUMBER
# undef SQLITE_VERSION_NUMBER
#endif

/ *
** CAPI3REF : 컴파일 시 라이브러리 의 버전 번호
**
** ^ ( SQLITE_VERSION ] sqlite3.h 헤더 에서 C 전 처리기 매크로
** 그 동안 의 SQLite 버전 인 문자열 리터럴 을 평가 하는
X는 주 버전 번호 ( 항상 3 용 입니다 ** 형식 " XYZ "
** SQLite3 의 ) 이며, Y는 부 버전 번호 이고 , Z는 릴리스 번호 입니다. ) ^
** ^ ( SQLITE_VERSION_NUMBER ] C 전처리 매크로 는 정수 에 해결
** 값이 ( X + Y * 1000000 * 1000 + Z ) X , Y 및 Z는 같은 경우
** [ SQLITE_VERSION 에서 사용되는 숫자입니다. ) ^
** SQLite는 하나 의 특정 릴리스에 대한 SQLITE_VERSION_NUMBER 의지도
** 그것이 유래 릴리스 보다 큰 것. Y 중 하나가 있겠지요
** 일정하게 유지하기위한 것이고 , Z가 증가 되거나 다른 Y 가 증가
** 및 Z는 0으로 재설정 된다.
**
** 버전 3.6.18 이후 SQLite 의 소스 코드 가 저장 되어 있습니다
** 만약, href = " http://www.fossil-scm.org/ " > 화석 구성 관리
** 시스템 < / A > . ^ SQLITE_SOURCE_ID 매크로 와 평가
** SQLite는 특정 체크인 을 식별하는 문자열
** 구성 관리 시스템 . ^ SQLITE_SOURCE_ID
** 문자열은 날짜 및 시간 체크인 ( UTC ) 의 및 SHA1 이 포함되어 있습니다
** 전체 소스 트리 의 해시 .
**
** 참조 : [ sqlite3_libversion ( ) ,
** [ sqlite3_libversion_number ( ) , sqlite3_sourceid ( ) ,
** [ sqlite_version ( ) 및 sqlite_source_id ( ) .
* /
#define SQLITE_VERSION        "3.8.3"
#define SQLITE_VERSION_NUMBER 3008003
#define SQLITE_SOURCE_ID      "2014-01-29 01:46:12 5bb29b82109224a2ad02920658fabd8fb0f27b3f"

/ *
** CAPI3REF : 런타임 라이브러리 의 버전 번호
** KEYWORDS : sqlite3_version , sqlite3_sourceid
**
**이 인터페이스는 , SQLITE_VERSION ] 와 같은 정보를 제공 하고
** [ SQLITE_VERSION_NUMBER ] 및 [ SQLITE_SOURCE_ID ] C 전처리 매크로
** 이 대신 헤더 파일 의 라이브러리 에 연결되어 있습니다. ^ ( 신중
** 프로그래머 의 적용 에서 assert ( ) 문이 포함 된 경우가
**이 인터페이스에서 반환 한 값은 매크로 와 일치 하는지 확인 하십시오
** 이와 같이, 헤더 및 응용 프로그램이 있다는 것을 보증
** 매칭 라이브러리와 헤더 파일을 사용하여 컴파일 .
**
** <BLOCKQUOTE> <PRE>
** 주장 ( sqlite3_libversion_number ( ) == SQLITE_VERSION_NUMBER ) ;
** 주장 ( strcmp 의 ( sqlite3_sourceid ( ) SQLITE_SOURCE_ID ) == 0 ) ;
** 주장 ( strcmp 의 ( sqlite3_libversion ( ) SQLITE_VERSION ) == 0 ) ;
** < / PRE > < / BLOCKQUOTE > ) ^
**
** ^ sqlite3_version [] 문자열 상수는 [ SQLITE_VERSION ] 텍스트 가 포함되어 있습니다
** 매크로 . ^ sqlite3_libversion ( ) 함수는 몸 에 대한 포인터를 반환
** sqlite3_version [] 문자열 상수 . sqlite3_libversion ( )
DLL 사용자가 일반적으로 가지고 있지 않기 때문에 ** 함수는 DLL의 사용을 위해 제공 되는
** DLL에 문자열 상수 에 직접 액세스 . ^
** sqlite3_libversion_number ( ) 함수 와 동일한 정수를 반환합니다.
** [ SQLITE_VERSION_NUMBER ] . ^ sqlite3_sourceid ( ) 함수가 반환
** 값 문자열 상수 에 대한 포인터 와 동일합니다
** [ SQLITE_SOURCE_ID ] C 전처리 매크로 .
**
** 참조 : [ sqlite_version ( ) 및 sqlite_source_id ( ) .
* /
SQLITE_API SQLITE_EXTERN const char sqlite3_version[];
SQLITE_API const char *sqlite3_libversion(void);
SQLITE_API const char *sqlite3_sourceid(void);
SQLITE_API int sqlite3_libversion_number(void);

/ *
** CAPI3REF : 런타임 라이브러리 의 컴파일 옵션 의 진단
**
** ^ sqlite3_compileoption_used ( ) 함수는 0 또는 1 을 반환합니다.
** 지정된 옵션이 정의 되었는지 여부를 나타내는
** 컴파일 시간. ^ SQLITE_ 접두사 생략 할 수있다
** sqlite3_compileoption_used 에 전달 옵션 이름 ( ) .
**
** ^ sqlite3_compileoption_get ( ) 함수는 반복 을 허용한다
** 에 의해 컴파일시 에 정의 된 옵션 목록 에
** N 번째 컴파일시의 옵션 문자열을 돌려 준다. ^ 만약 N 이 범위 외인 ,
** sqlite3_compileoption_get ( ) NULL 포인터를 반환합니다. ^ SQLITE_
** 접두사 는 반환 된 문자열을 생략하고있다
** sqlite3_compileoption_get ( ) .
**
** ^ sqlite3_compileoption_used 진단 기능 지원 ( )
** 와 sqlite3_compileoption_get ( ) 를 지정하여 생략 할 수있다
컴파일 시 에 ** [ SQLITE_OMIT_COMPILEOPTION_DIAGS 옵션을 선택합니다.
**
** 참조 : SQL 함수 [ sqlite_compileoption_used ( ) 및
** [ sqlite_compileoption_get ( ) 및 compile_options 프라 그마 ] .
* /
#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
SQLITE_API int sqlite3_compileoption_used(const char *zOptName);
SQLITE_API const char *sqlite3_compileoption_get(int N);
#endif

/ *
** CAPI3REF : 라이브러리 는 스레드 로부터 안전한지 여부 를 테스트 하기 위해 참조하십시오
**
** ^ sqlite3_threadsafe ( ) 함수가 반환 제로 와 경우에만
** SQLite 것이 원인이 생략 mutex 화 코드를 사용하여 컴파일 된
** [ SQLITE_THREADSAFE ] 컴파일 시 의 옵션이 0으로 설정되어 있다.
**
** SQLiteはとか뮤텍스 않고 컴파일 할 수 있습니다. 시간
** [ SQLITE_THREADSAFE ] C 전처리 매크로 는 1 또는 2, 뮤텍스입니다
** 이 활성화되어 있으며, SQLite 는 스레드로부터 안전 합니다. 시간
** [ SQLITE_THREADSAFE 매크로 는 0 이다
** 뮤텍스는 생략 하고있다. 뮤텍스 가 없으면 그것은 안전 하지 않습니다
** 여러 스레드에서 동시에 SQLite 를 사용 한다.
**
** 뮤텍스를 사용하면 측정 가능한 성능 저하 가 발생합니다.
속도가 가장 중요한 경우 에는 ** 그래서, 그것은 비활성화 하는 의미가 있습니다
** 뮤텍스 . 그러나 최대 의 안전을 위해 뮤텍스를 활성화 해야 합니다.
뮤텍스를 사용 하기 위해 ** ^ 기본 동작입니다.
**
** 이 인터페이스는 것을 확인하기 위해 응용 프로그램에서 사용할 수 있습니다
** 그것은 에 링크 되어있는 SQLite 버전 에서 컴파일 된
** [ SQLITE_THREADSAFE 매크로 목표 설정.
**
** 이 인터페이스는 컴파일 타임 뮤텍스 설정 에 신고
** [ SQLITE_THREADSAFE ] 플래그 . SQLite 는 컴파일 된 경우
** SQLITE_THREADSAFE = 1 또는 = 2 다음 뮤텍스는 기본적으로 활성화되어 있습니다 만,
** 완전히 또는 부분적으로 [ ) ( sqlite3_config ] 에 대한 호출을 사용하여 해제 할 수 있습니다
** 동사 에서 SQLITE_CONFIG_SINGLETHREAD , SQLITE_CONFIG_MULTITHREAD ]
** 또는 SQLITE_CONFIG_MUTEX ] . 노 ^ ( 반환 값
** sqlite3_threadsafe ( ) 함수는 컴파일시 구성 을 보여줍니다
** 스레드로부터 그 설정 에 대한 런타임 변경 에 의해 수행 되지 않은
** sqlite3_config ( ) . 즉, 반환 값 sqlite3_threadsafe 에서 ( )
** ) ( sqlite3_config 의 호출로 변경 되지 않습니다. ) ^
**
** 자세한 내용은 스레드 모드 설명서를 참조 하십시오.
* /
SQLITE_API int sqlite3_threadsafe(void);

/ * 
** CAPI3REF : 데이터베이스 연결 핸들 
** KEYWORDS : {데이터베이스 연결} {데이터베이스 연결} 
** 
** 각 오픈 된 SQLite 데이터베이스 인스턴스의 포인터로 표현된다 
** 불투명 한 구조 "는 sqlite3의"라는. 그것은 sqlite3 생각은 유용하다 
** 개체로의 포인터. [에서 sqlite3_open (), sqlite3_open16 () 및 
** [sqlite3_open_v2 () 인터페이스는 생성자에서 sqlite3_close () 
** 및 sqlite3_close_v2 () 소멸자입니다. 다른 많은 것이 있습니다 
** 인터페이스 (예 : 
** [sqlite3_prepare_v2 (), sqlite3_create_function () 및 
** 이름은 3 [sqlite3_busy_timeout ()])의 방법이 있다는 것을 
** sqlite3 개체입니다. 
* /
typedef struct sqlite3 sqlite3;
/ * 
** CAPI3REF : 64 비트 정수형 
** KEYWORDS : sqlite_int64 sqlite_uint64 
** 
** 64 비트 정수를 지정하는 크로스 플랫폼 방법이 없기 때문에 
** SQLite는 64 비트 부호있는 및 부호없는 정수 형식 정의가 포함되어 있습니다. 
** 
** sqlite3_int64과 sqlite3_uint64은 바람직한 형태의 정의입니다. 
** sqlite_int64과 sqlite_uint64 유형이 후방에서 지원됩니다 
** 호환 만. 
** 
** ^ sqlite3_int64과 sqlite_int64 유형은 정수 값을 저장할 수 있습니다 
** 포괄적 -9223372036854775808 사이 9223372036854775807. ^ 
** sqlite3_uint64과 sqlite_uint64 유형은 정수 값을 저장할 수 있습니다 
** 포괄적 0 ~ 18446744073709551615. 
* /
#ifdef SQLITE_INT64_TYPE
  typedef SQLITE_INT64_TYPE sqlite_int64;
  typedef unsigned SQLITE_INT64_TYPE sqlite_uint64;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 sqlite_int64;
  typedef unsigned __int64 sqlite_uint64;
#else
  typedef long long int sqlite_int64;
  typedef unsigned long long int sqlite_uint64;
#endif
typedef sqlite_int64 sqlite3_int64;
typedef sqlite_uint64 sqlite3_uint64;

/*
** If compiling for a processor that lacks floating point support,
** substitute integer for floating-point.
*/
#ifdef SQLITE_OMIT_FLOATING_POINT
# define double sqlite3_int64
#endif

/ *
** CAPI3REF : 폐회 데이터베이스 연결
**
** ^ sqlite3_close ( ) 와 sqlite3_close_v2 ( ) 루틴은 소멸자
** [ sqlite3 의 개체 의 .
** ^ 반환 SQLITE_OK ) ( ) 와 sqlite3_close_v2 을 ( sqlite3_close 하는 호출하는 경우
** [ sqlite3 의 개체가 성공적으로 파기되어 관련된 모든
** 자원이 할당 해제 됩니다.
**
** ^ 데이터베이스 연결이 종료되지 않은 준비 에 연결된 경우
** 문장 또는 미완성 sqlite3_backup 개체 다음 sqlite3_close ( )
** 오픈 데이터베이스 연결 유지 하고 SQLITE_BUSY ] 돌려 준다.
** ^ sqlite3_close_v2 ( ) 가 종료되지 않은 준비된 문 에서 호출 된 경우
** 와 미완성 sqlite3_backups 데이터베이스 연결 됩니다
** 자동 으로 해제됩니다 사용할 수 없게되는 '좀비' 때
** 마지막 준비 문장 을 확인하거나 마지막 sqlite3_backup 이 가
** 끝났습니다 . sqlite3_close_v2 ( ) 인터페이스는 사용 하기 때문 입니다
가비지 수집 된 ** 호스트 언어 및 별
** 소멸자가 호출되는 선택이다 .
**
** 응용 프로그램 이어야 [ sqlite3_finalize | 종료 ] 모든 [ 준비된 문 ]
** [ sqlite3_blob_close | 닫기 ] 를 모두 [ BLOB 핸들 , 및
** [ sqlite3_backup_finish | 마침 모두 [ sqlite3_backup 개체가 연결된
** 이전 개체를 닫으려고 하면 sqlite3 의 ] 목적으로한다. ^ 만약
** sqlite3_close_v2 ( ) 은 지금도 가지고 데이터베이스 연결에서 호출되는
** 발행 [ 준비된 문 , BLOB 핸들 , 및 / 또는
** [ sqlite3_backup 개체 , 그것은 SQLITE_OK 가 할당 해제 를 반환
** 모든 리소스 [ 준비된 문 , BLOB 핸들 ] 까지 연기되고
** 및 sqlite3_backup 개체 도 삭제 됩니다.
**
** ^ 트랜잭션이 열려있는 동안 은 [ sqlite3 의 개체 가 삭제되는 경우
** 트랜잭션이 자동으로 롤백 됩니다.
**
** [ sqlite3_close ( C ) 및 sqlite3_close_v2 ( C ) ] 에서 C 매개 변수
** NULL 중 하나 여야 합니다
** 포인터 또는 검색 [ sqlite3 의 개체 포인터
** [에서 sqlite3_open ( ) ]에서 [ sqlite3_open16 ( ) 또는
** [ sqlite3_open_v2 ( ) 및 이전에 닫혀 있지 않다.
** ^ NULL 포인터 sqlite3_close ( ) 또는 sqlite3_close_v2 ( ) 를 호출
** 인수는 무해 무 조작 입니다.
* /
SQLITE_API int sqlite3_close(sqlite3*);
SQLITE_API int sqlite3_close_v2(sqlite3*);

/*
** The type for a callback function.
** This is legacy and deprecated.  It is included for historical
** compatibility and is not documented.
*/
typedef int (*sqlite3_callback)(void*,int,char**, char**);

/*
** CAPI3REF : 원스텝 쿼리 실행 인터페이스
**
** sqlite3_exec ( ) 인터페이스는 주위 의 편리한 래퍼입니다
** [ sqlite3_prepare_v2 ( ) , sqlite3_step ( ) ] 및 [ sqlite3_finalize ( ) ,
** 즉, 응용 프로그램이 SQL 의 여러 문을 실행할 수 있습니다
** C 코드를 많이 사용할 필요가 없습니다.
**
** ^ sqlite3_exec ( ) 인터페이스는 제로 또는 UTF - 8 인코딩 정보 를 실행 합니다
** 세미콜론으로 별도의 제 2 인수 로 전달 된 SQL 문 을
** 데이터베이스 연결 의 컨텍스트에서 그 첫 번째 로 전달
** 인수 . ^ 경우 에는 세 번째 인수 의 콜백 함수에
** sqlite3_exec ( ) 는 NULL이 아닙니다 , 그것은 각각 의 결과 행에 대해 호출됩니다
** 평가 된 SQL 문 에서 나온다. ^ 의 제 4 인수
** sqlite3_exec ( ) 각각 제 1 인수 에 이르기까지 중계 되고
** 콜백 의 호출 . ^ 콜백 포인터가 sqlite3_exec 한 경우 ( )
** NULL의 경우, 콜백은 지금까지 호출되지 않고 결과 행이 함
** 무시 .
**
** ^ 에 전달 된 SQL 문을 평가 하는 동안 오류가 발생한 경우
** sqlite3_exec ( ) 는 현재 명령문의 실행 이 중지되고
** 후속 문장은 생략 됩니다. ^ 다섯 번째 매개 변수가 sqlite3_exec 한 경우 ( )
** NULL 어떤 오류 메시지가 얻은 메모리 에 기록 되지 않습니다
** 에서 sqlite3_malloc ( ) 및 백 다섯 번째 매개 변수를 통과 시켰다.
** 메모리 누수를 방지 하기 위해 응용 프로그램 은 [ ) ( sqlite3_free 를 호출 해야합니다
** 오류 메시지 문자열 중 5 매개 변수를 통해 반환되는
** sqlite3_exec 의 ( ) 오류 메시지 문자열 은 더이상 필요하지 않다 후.
** ^ sqlite3_exec 다섯째 매개 변수 ( ) 는 오류 를 NULL이 아닌 아니라고 한 경우
** 발생 후 sqlite3_exec ( ) 의 다섯 번째 매개 변수 에 포인터를 설정한다
** 가기 전에 NULL입니다.
**
** ^ sqlite3_exec ( ) 콜백이 제로 를 반환하면 sqlite3_exec ( )
** 돌아가서 다시 콜백 을 호출하지 않고 SQLITE_ABORT 과
** 후속 SQL 문을 실행 하지 않고.
**
** ^ sqlite3_exec ( ) 콜백 함수의 제 2 인수가
** 결과 열 수. ^ sqlite3_exec 의 제 3 인수 ( )
** 콜백 에서 있는 것처럼 취득한 캐릭터 라인의 포인터 의 배열입니다
** [ sqlite3_column_text ( ) ] 각 열의 1. ^ 경우 요소
** 결과 행 은 다음 에 해당 하는 문자열 포인터가 NULL 이다
** sqlite3_exec ( ) 콜백이 NULL 포인터 이다. ^ 의 제 4 인수
** sqlite3_exec ( ) 콜백은 문자열 에 대한 포인터 의 배열입니다 각
얻어진 ** 항목은 해당 결과 열 이름을 나타냅니다
** 에서 sqlite3_column_name ( ) .
**
** ^ sqlite3_exec 하는 두 번째 매개 변수 ( ) 이 NULL 포인터 의 경우 포인터
** 빈 문자열 또는 공백 만 및 / 또는 이 포함 된 포인터 에
** SQL 댓글 은 어떤 SQL 문 은 데이터베이스 에 평가 되어 있지 않다고 하는
** 변경되지 않습니다.
**
** 제한 :
**
** <UL>
** 응용 프로그램 은 첫 번째 매개 변수가 sqlite3_exec 하는 것을 보장해야 한다 <LI> ( )
** 유효하고 오픈 데이터베이스 연결 이다.
** 응용 프로그램 <LI> 에서 지정된 데이터베이스 연결을 닫지 말라 없습니다
sqlite3_exec ( ) 가 실행되고 있는 동안 ** 첫번째 매개 변수 ( ) sqlite3_exec 한다.
** 응용 프로그램 <LI> 에 전달 된 SQL 문 텍스트를 변경 해서는 안
** sqlite3_exec 의 두 번째 매개 변수 ( ) sqlite3_exec ( ) 실행 중.
** < / UL >
* /
SQLITE_API int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);
/ * 
** CAPI3REF : 결과 코드 
** KEYWORDS : SQLITE_OK {오류 코드} {오류 코드} 
** KEYWORDS : {결과 코드} {결과 코드} 
** 
** 여러 SQLite 함수가 가리키는 집합에서 정수 결과 코드를 반환 
** 여기에서 성공했는지 실패했는지를 보여주기 위하여. 
** 
** 새로운 오류 코드는 SQLite의 향후 버전에서 추가 할 수 있었다. 
** 
** 참조 : [SQLITE_IOERR_READ | 확장 결과 코드, 
** [sqlite3_vtab_on_conflict ()] [SQLITE_ROLLBACK | 결과 코드. 
* /
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* SQL error or missing database */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* Unknown opcode in sqlite3_file_control() */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* Database lock protocol error */
#define SQLITE_EMPTY       16   /* Database is empty */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Auxiliary database format error */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_NOTICE      27   /* Notifications from sqlite3_log() */
#define SQLITE_WARNING     28   /* Warnings from sqlite3_log() */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */
/* end-of-error-codes */

/ *
** CAPI3REF : 확장 결과 코드
** KEYWORDS : { 확장 오류 코드 } { 확장 오류 코드 }
** KEYWORDS : { 확장 결과 코드 } { 확장 결과 코드 }
**
** 기본 설정은 SQLite 의 API 루틴 은 26 의 정수 중 하나를 반환
** [ SQLITE_OK | 결과 코드 . 그러나 경험이 보여주고 있다는 많은
**이 결과 코드는 너무 야한 이다. 그들은 같이 제공 하지 않습니다
** 프로그래머 등 의 문제 에 대한 많은 정보 가 좋아할지도 모른다. 노력 중
** 이 처리하는 SQLite는 ( 버전 3.3.8 이상) 의 최신 버전 은
** 보다 자세한 정보를 제공하는 추가 결과 코드 지원
** 오류 에 관한 것이다. 확장 결과 코드를 활성화 또는 비활성화 하는
** 사용하여 데이터베이스에 대해 연결 기준으로
** [ sqlite3_extended_result_codes ( ) API입니다.
**
** 사용 가능한 확장 결과 코드 의 일부는 여기 에 나열되어 있습니다.
** 하나는 확장 결과 코드 의 수가 증가 할 것으로 예상 할 수
** 시간 을 가져봐. 확장 된 결과 코드를 사용 하는 소프트웨어는 기대 하십시오
** SQLite는 향후 릴리스 에서 새로운 결과 코드를 참조 하십시오.
**
** SQLITE_OK 결과 코드 가 연장 되는 것은 아닙니다. 항상 입니다
** 엄격하게 0이다.
* /
#define SQLITE_IOERR_READ              (SQLITE_IOERR | (1<<8))
#define SQLITE_IOERR_SHORT_READ        (SQLITE_IOERR | (2<<8))
#define SQLITE_IOERR_WRITE             (SQLITE_IOERR | (3<<8))
#define SQLITE_IOERR_FSYNC             (SQLITE_IOERR | (4<<8))
#define SQLITE_IOERR_DIR_FSYNC         (SQLITE_IOERR | (5<<8))
#define SQLITE_IOERR_TRUNCATE          (SQLITE_IOERR | (6<<8))
#define SQLITE_IOERR_FSTAT             (SQLITE_IOERR | (7<<8))
#define SQLITE_IOERR_UNLOCK            (SQLITE_IOERR | (8<<8))
#define SQLITE_IOERR_RDLOCK            (SQLITE_IOERR | (9<<8))
#define SQLITE_IOERR_DELETE            (SQLITE_IOERR | (10<<8))
#define SQLITE_IOERR_BLOCKED           (SQLITE_IOERR | (11<<8))
#define SQLITE_IOERR_NOMEM             (SQLITE_IOERR | (12<<8))
#define SQLITE_IOERR_ACCESS            (SQLITE_IOERR | (13<<8))
#define SQLITE_IOERR_CHECKRESERVEDLOCK (SQLITE_IOERR | (14<<8))
#define SQLITE_IOERR_LOCK              (SQLITE_IOERR | (15<<8))
#define SQLITE_IOERR_CLOSE             (SQLITE_IOERR | (16<<8))
#define SQLITE_IOERR_DIR_CLOSE         (SQLITE_IOERR | (17<<8))
#define SQLITE_IOERR_SHMOPEN           (SQLITE_IOERR | (18<<8))
#define SQLITE_IOERR_SHMSIZE           (SQLITE_IOERR | (19<<8))
#define SQLITE_IOERR_SHMLOCK           (SQLITE_IOERR | (20<<8))
#define SQLITE_IOERR_SHMMAP            (SQLITE_IOERR | (21<<8))
#define SQLITE_IOERR_SEEK              (SQLITE_IOERR | (22<<8))
#define SQLITE_IOERR_DELETE_NOENT      (SQLITE_IOERR | (23<<8))
#define SQLITE_IOERR_MMAP              (SQLITE_IOERR | (24<<8))
#define SQLITE_IOERR_GETTEMPPATH       (SQLITE_IOERR | (25<<8))
#define SQLITE_IOERR_CONVPATH          (SQLITE_IOERR | (26<<8))
#define SQLITE_LOCKED_SHAREDCACHE      (SQLITE_LOCKED |  (1<<8))
#define SQLITE_BUSY_RECOVERY           (SQLITE_BUSY   |  (1<<8))
#define SQLITE_BUSY_SNAPSHOT           (SQLITE_BUSY   |  (2<<8))
#define SQLITE_CANTOPEN_NOTEMPDIR      (SQLITE_CANTOPEN | (1<<8))
#define SQLITE_CANTOPEN_ISDIR          (SQLITE_CANTOPEN | (2<<8))
#define SQLITE_CANTOPEN_FULLPATH       (SQLITE_CANTOPEN | (3<<8))
#define SQLITE_CANTOPEN_CONVPATH       (SQLITE_CANTOPEN | (4<<8))
#define SQLITE_CORRUPT_VTAB            (SQLITE_CORRUPT | (1<<8))
#define SQLITE_READONLY_RECOVERY       (SQLITE_READONLY | (1<<8))
#define SQLITE_READONLY_CANTLOCK       (SQLITE_READONLY | (2<<8))
#define SQLITE_READONLY_ROLLBACK       (SQLITE_READONLY | (3<<8))
#define SQLITE_READONLY_DBMOVED        (SQLITE_READONLY | (4<<8))
#define SQLITE_ABORT_ROLLBACK          (SQLITE_ABORT | (2<<8))
#define SQLITE_CONSTRAINT_CHECK        (SQLITE_CONSTRAINT | (1<<8))
#define SQLITE_CONSTRAINT_COMMITHOOK   (SQLITE_CONSTRAINT | (2<<8))
#define SQLITE_CONSTRAINT_FOREIGNKEY   (SQLITE_CONSTRAINT | (3<<8))
#define SQLITE_CONSTRAINT_FUNCTION     (SQLITE_CONSTRAINT | (4<<8))
#define SQLITE_CONSTRAINT_NOTNULL      (SQLITE_CONSTRAINT | (5<<8))
#define SQLITE_CONSTRAINT_PRIMARYKEY   (SQLITE_CONSTRAINT | (6<<8))
#define SQLITE_CONSTRAINT_TRIGGER      (SQLITE_CONSTRAINT | (7<<8))
#define SQLITE_CONSTRAINT_UNIQUE       (SQLITE_CONSTRAINT | (8<<8))
#define SQLITE_CONSTRAINT_VTAB         (SQLITE_CONSTRAINT | (9<<8))
#define SQLITE_CONSTRAINT_ROWID        (SQLITE_CONSTRAINT |(10<<8))
#define SQLITE_NOTICE_RECOVER_WAL      (SQLITE_NOTICE | (1<<8))
#define SQLITE_NOTICE_RECOVER_ROLLBACK (SQLITE_NOTICE | (2<<8))
#define SQLITE_WARNING_AUTOINDEX       (SQLITE_WARNING | (1<<8))

/ * 
** CAPI3REF : 파일 열기 작업 플래그 
** 
**이 비트는에서의 사용을 의도하고있다 
** [sqlite3_open_v2 ()에서 세 번째 매개 변수 인터페이스와 
** [sqlite3_vfs.xOpen] 메서드의 네 번째 매개 변수입니다. 
* /
#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_DELETEONCLOSE    0x00000008  /* VFS only */
#define SQLITE_OPEN_EXCLUSIVE        0x00000010  /* VFS only */
#define SQLITE_OPEN_AUTOPROXY        0x00000020  /* VFS only */
#define SQLITE_OPEN_URI              0x00000040  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_MEMORY           0x00000080  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_MAIN_DB          0x00000100  /* VFS only */
#define SQLITE_OPEN_TEMP_DB          0x00000200  /* VFS only */
#define SQLITE_OPEN_TRANSIENT_DB     0x00000400  /* VFS only */
#define SQLITE_OPEN_MAIN_JOURNAL     0x00000800  /* VFS only */
#define SQLITE_OPEN_TEMP_JOURNAL     0x00001000  /* VFS only */
#define SQLITE_OPEN_SUBJOURNAL       0x00002000  /* VFS only */
#define SQLITE_OPEN_MASTER_JOURNAL   0x00004000  /* VFS only */
#define SQLITE_OPEN_NOMUTEX          0x00008000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_FULLMUTEX        0x00010000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_SHAREDCACHE      0x00020000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_PRIVATECACHE     0x00040000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_WAL              0x00080000  /* VFS only */

/* Reserved:                         0x00F00000 */

/ *
** CAPI3REF : 장치 의 특성
**
** [ sqlite3_io_methods ] 의 xDeviceCharacteristics 방법은
** 목적은 이러한 벡터 를 나타내는 정수 를 반환
대용량 저장 장치 I / O 특성을 발현 ** 비트 값
** [ sqlite3_io_methods 파일을 보유하고있는 장치
** 를 말합니다.
**
** SQLITE_IOCAP_ATOMIC 속성은 의미 의 모든 기록
** 모든 크기 는 원자 입니다. SQLITE_IOCAP_ATOMICnnn 값
** 크기는 NNN 바이트 블록으로 기록하는 것을 의미하고,
** 는의 정수 수배의 주소 에 정렬 하는
** NNN 은 원자 입니다. SQLITE_IOCAP_SAFE_APPEND 값 수단
데이터 가 파일 에 추가 된 경우 ** 데이터가 추가 되어 있는지
** 먼저 파일 의 크기 가 다른 것은 없는 확장 된
** 도로 주변. SQLITE_IOCAP_SEQUENTIAL 속성은 의미
** 정보는 호출과 동일한 순서로 디스크 에 기록 된
** xWrite 에 ( ) . SQLITE_IOCAP_POWERSAFE_OVERWRITE 속성은 의미
** 후 충돌이나 정전 바이트 만 다음 다시 시작
** 응용 프로그램 레벨에서 작성된 파일이 변경 되었을 수 있습니다
** 및 인접 바이트 는 같은 부문에서 이어도 바이트 가 있다는 것을
** 불변 인 것이 보증 되었습니다. SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN
** 플래그는 때 열려있는 파일을 삭제할 수 없는 것을 나타낸다.
* /
#define SQLITE_IOCAP_ATOMIC                 0x00000001
#define SQLITE_IOCAP_ATOMIC512              0x00000002
#define SQLITE_IOCAP_ATOMIC1K               0x00000004
#define SQLITE_IOCAP_ATOMIC2K               0x00000008
#define SQLITE_IOCAP_ATOMIC4K               0x00000010
#define SQLITE_IOCAP_ATOMIC8K               0x00000020
#define SQLITE_IOCAP_ATOMIC16K              0x00000040
#define SQLITE_IOCAP_ATOMIC32K              0x00000080
#define SQLITE_IOCAP_ATOMIC64K              0x00000100
#define SQLITE_IOCAP_SAFE_APPEND            0x00000200
#define SQLITE_IOCAP_SEQUENTIAL             0x00000400
#define SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN  0x00000800
#define SQLITE_IOCAP_POWERSAFE_OVERWRITE    0x00001000

/*
** CAPI3REF: File Locking Levels
**
** SQLite uses one of these integer values as the second
** argument to calls it makes to the xLock() and xUnlock() methods
** of an [sqlite3_io_methods] object.
*/
#define SQLITE_LOCK_NONE          0
#define SQLITE_LOCK_SHARED        1
#define SQLITE_LOCK_RESERVED      2
#define SQLITE_LOCK_PENDING       3
#define SQLITE_LOCK_EXCLUSIVE     4

/ *
** CAPI3REF : 동기화 옵션 플래그
**
** SQLite 는의 XSYNC ( ) 메서드를 호출하면
** [ sqlite3_io_methods ] 그것은 조합을 사용 하는 개체
** 둘째 인수로 이러한 정수 값입니다.
**
SQLITE_SYNC_DATAONLY 플래그가 사용되는 경우 ** 는 의미
** 동기화 작업은 대용량 스토리지 에 데이터를 플러시 해야 합니다. i 노드
** 정보가 플래시 될 필요 는 없습니다. 만약 플래그 의 하위 4 비트
** 동일한 SQLITE_SYNC_NORMAL , 즉 일반 fsync ( ) 시멘틱스를 사용 하는 것을 의미 합니다.
** 하위 4 비트는 SQLITE_SYNC_FULL 와 같으면 그 수단
** Mac OS X 의 스타일 fullsync 대신 fsync ( ) 를 사용 합니다.
**
** SQLITE_SYNC_NORMAL 과 SQLITE_SYNC_FULL 플래그를 혼동 하지 마십시오
** [ 프라 그마 동기화 에 = 통상 및 프라 그마 동기화 이 FULL
** 설정 . [ 동기화 프라 그마 ] 은 판단했을 경우 에 호출
** XSYNC 의 VFS 방법 이 발생 하고 모든 플랫폼에서 동일하게 적용 됩니다.
** SQLITE_SYNC_NORMAL 과 SQLITE_SYNC_FULL 플래그가 어떻게 결정 하는가?
** 정력 엄격 하거나 강제 동기화 작업 이 있으면
** 기본 SQLite 의 코드는 Mac OSX 에서 차이가 난다.
** ( 타사 의 VFS 구현 도 구별 을 할지도 모른다
** SQLITE_SYNC_NORMAL 과 SQLITE_SYNC_FULL 사이 가 사이
기본 SQLite 의 유일한 Mac OSX 버전 에서 지원 되고있다. ** 운영 체제
** 차이 에 대한 관심. )
* /
#define SQLITE_SYNC_NORMAL        0x00002
#define SQLITE_SYNC_FULL          0x00003
#define SQLITE_SYNC_DATAONLY      0x00010
/ * 
** CAPI3REF : OS의 인터페이스의 오픈 파일 핸들 
** 
** [sqlite3_file] 개체에서 열린 파일을 나타내는 
** [sqlite3_vfs | OS의 인터페이스 계층]. 개별 OS의 인터페이스 
** 구현 의지 
** 추가 필드를 추가하여이 개체를 서브 클래 싱하고 싶다 
** 개인. pMethods 항목에 대한 포인터이다 
실행하는 방법을 정의합니다 ** [sqlite3_io_methods 개체 
** I / O가 오픈 된 파일에 대한 작업. 
* /
typedef struct sqlite3_file sqlite3_file;
struct sqlite3_file {
  const struct sqlite3_io_methods *pMethods;  /* Methods for an open file */
};

/ *
** CAPI3REF : OS 의 인터페이스는 가상 메서드 개체 파일
**
** [ sqlite3_vfs.xOpen ] 메소드에 의해 활성화 된 모든 파일이 채워집니다
더 일반적으로 ** [ sqlite3_file 개체 ( 또는 그 서브 클래스
** [ sqlite3_file 이 개체 의 인스턴스에 대한 포인터 를 가진 개체 ) .
** 이 개체는 다양한 작업을 수행 하는 데 사용 하는 메서드를 정의
** [ sqlite3_file 개체 로 표시되는 열려있는 파일에 대해 .
**
** [ sqlite3_vfs.xOpen ] 방법은 sqlite3_file.pMethods 요소를 설정 한 경우
** 비 NULL 포인터 에는 sqlite3_io_methods.xClose 방법
[ sqlite3_vfs.xOpen ] 그것이 실패 했다고 보도했다 경우에도 ** 호출 할 수 있습니다. 더
** 실패 [ sqlite3_vfs.xOpen ] 다음 XCLOSE 하기위한 호출 을 방지하기위한 유일한 방법 은
[ sqlite3_vfs.xOpen ] sqlite3_file.pMethods 요소를 설정하는 ** 입니다
** NULL로 .
**
** XSYNC 의 flags 인수는 SQLITE_SYNC_NORMAL ] 의 1 이상 이다
** [ SQLITE_SYNC_FULL ] . 첫 번째 선택은 성공적으로 fsync ( ) 입니다.
** 번째 옵션은 Mac OS X 풍의 fullsync 입니다. [ SQLITE_SYNC_DATAONLY ]
** 를 나타내는 플래그 에 OR 연산 되어 그 파일 의 데이터 만
** 없이 그 i 노드가 동기화 해야 합니다.
**
** XLOCK ( ) 와 xUnlock 의 정수 값은 ( ) 중 하나입니다
** <UL>
** <LI> [ SQLITE_LOCK_NONE ]
** <LI> [ SQLITE_LOCK_SHARED ]
** <LI> [ SQLITE_LOCK_RESERVED ]
** <LI> [ SQLITE_LOCK_PENDING 또는
** <LI> [ SQLITE_LOCK_EXCLUSIVE ] .
** < / UL >
** XLOCK ( ) 잠금을 향상 시킵니다. xUnlock 는 () 락을 감소시킨다.
** xCheckReservedLock ( ) 메서드를 검사 할지 여부 모든 데이터베이스 연결
** 이 프로세스 나 다른 프로세스 중 하나 에서 RESERVED 을 보유하고
** 보류 또는 파일 에 대한 단독 잠금 . 이것은 true를 돌려줍니다
** 이러한 잠금이 존재 하고 , 그렇지 않으면 false입니다.
**
** xFileControl ( ) 메서드는 사용자 지정 을 가능하게하는 일반적인 인터페이스 이다
직접 사용하여 열려있는 파일 관리 ** VFS 는 구현
** [ sqlite3_file_control ( ) 인터페이스. 두 번째 " OP " 인수가
** 정수 연산 코드. 세번째 인수 는 의도 된 일반적인 포인터 이다
** 여기에 인수 또는 공백을 포함 할 수있다 구조에 대한
** 쓰기 반환 . xFileControl 위한 잠재적 인 용도 ( ) 일지도 모릅니다
** 의 기능은 변경 될 수 제한 잠금을 차단할 수 있도록 하는
** 문의 는 ( 예를 들어, 도트 파일 잠금을 사용 하는 ) 전략 을 잠 그려면
** 잠금 상태 또는 오래된 잠금을 깨는 . SQLite는
** 코어 매장 모든 작동 코드 가 자체 사용을 위해 100 미만 .
** A는 [ SQLITE_FCNTL_LOCKSTATE | 작동 코드 목록 이 100 미만 으로 볼 수 있습니다.
** 사용자 지정 xFileControl 메서드를 정의 하는 응용 프로그램은 opcode를 사용 해야 합니다
** 100 개 이상의 충돌을 피하기 위해. VFS 구현 해야
** 반환 [ SQLITE_NOTFOUND ] 파일 제어 작동 코드 때문에 하지 않다는
** 인식 하고 있습니다 .
**
** xSectorSize ( ) 메서드는 섹터 크기를 반환합니다.
** 파일 의 기본 장치 . 섹터 크기 이다
방해하지 않고 실행할 수 있습니다. ** 최소 쓰기
파일의 ** 다른 바이트 . xDeviceCharacteristics ( )
** 방법은 행동을 설명하는 비트 벡터를 돌려줍니다.
** 내부 장치 .
**
** <UL>
** <LI> [ SQLITE_IOCAP_ATOMIC ]
** <LI> [ SQLITE_IOCAP_ATOMIC512 ]
** <LI> [ SQLITE_IOCAP_ATOMIC1K ]
** <LI> [ SQLITE_IOCAP_ATOMIC2K ]
** <LI> [ SQLITE_IOCAP_ATOMIC4K ]
** <LI> [ SQLITE_IOCAP_ATOMIC8K ]
** <LI> [ SQLITE_IOCAP_ATOMIC16K ]
** <LI> [ SQLITE_IOCAP_ATOMIC32K ]
** <LI> [ SQLITE_IOCAP_ATOMIC64K ]
** <LI> [ SQLITE_IOCAP_SAFE_APPEND ]
** <LI> [ SQLITE_IOCAP_SEQUENTIAL ]
** < / UL >
**
** SQLITE_IOCAP_ATOMIC 속성은 의미 의 모든 기록
** 모든 크기 는 원자 입니다. SQLITE_IOCAP_ATOMICnnn 값
** 크기는 NNN 바이트 블록으로 기록하는 것을 의미하고,
** 는의 정수 수배의 주소 에 정렬 하는
** NNN 은 원자 입니다. SQLITE_IOCAP_SAFE_APPEND 값 수단
데이터 가 파일 에 추가 된 경우 ** 데이터가 추가 되어 있는지
** 먼저 파일 의 크기 가 다른 것은 없는 확장 된
** 도로 주변. SQLITE_IOCAP_SEQUENTIAL 속성은 의미
** 정보는 호출과 동일한 순서로 디스크 에 기록 된
** xWrite 에 ( ) .
**
** 만약 XREAD ( ) 가 반환 그것은 또한 입력 해야 합니다 SQLITE_IOERR_SHORT_READ
** 제로 버퍼 읽지 않은 부분. VFS 수
** 실패 간편 0 채우기 동작 하는 것처럼 보일지도 모릅니다 읽습니다. 그러나
** 실패 에 짧은 제로 매장 로드 는 결국 이어질
** 데이터베이스 손상 .
* /
typedef struct sqlite3_io_methods sqlite3_io_methods;
struct sqlite3_io_methods {
  int iVersion;
  int (*xClose)(sqlite3_file*);
  int (*xRead)(sqlite3_file*, void*, int iAmt, sqlite3_int64 iOfst);
  int (*xWrite)(sqlite3_file*, const void*, int iAmt, sqlite3_int64 iOfst);
  int (*xTruncate)(sqlite3_file*, sqlite3_int64 size);
  int (*xSync)(sqlite3_file*, int flags);
  int (*xFileSize)(sqlite3_file*, sqlite3_int64 *pSize);
  int (*xLock)(sqlite3_file*, int);
  int (*xUnlock)(sqlite3_file*, int);
  int (*xCheckReservedLock)(sqlite3_file*, int *pResOut);
  int (*xFileControl)(sqlite3_file*, int op, void *pArg);
  int (*xSectorSize)(sqlite3_file*);
  int (*xDeviceCharacteristics)(sqlite3_file*);
  /* Methods above are valid for version 1 */
  int (*xShmMap)(sqlite3_file*, int iPg, int pgsz, int, void volatile**);
  int (*xShmLock)(sqlite3_file*, int offset, int n, int flags);
  void (*xShmBarrier)(sqlite3_file*);
  int (*xShmUnmap)(sqlite3_file*, int deleteFlag);
  /* Methods above are valid for version 2 */
  int (*xFetch)(sqlite3_file*, sqlite3_int64 iOfst, int iAmt, void **pp);
  int (*xUnfetch)(sqlite3_file*, sqlite3_int64 iOfst, void *p);
  /* Methods above are valid for version 3 */
  /* Additional methods may be added in future releases */
};

/ *
** CAPI3REF : 표준 파일 제어 작동 코드
**
**이 정수 는 xFileControl 메서드 의 작동 코드 입니다
** [ sqlite3_io_methods 개체 와 용 [ sqlite3_file_control ( )
** 인터페이스.
**
** [ SQLITE_FCNTL_LOCKSTATE ] opcode가 디버깅 을 위해 사용되고 있다. 이
** opcode가 xFileControl 방법은 현재 의 상태를 기록 하는
** 잠금 ( SQLITE_LOCK_NONE ] 1 [ SQLITE_LOCK_SHARED ]
** [ SQLITE_LOCK_RESERVED , SQLITE_LOCK_PENDING ] 또는 SQLITE_LOCK_EXCLUSIVE ] )
** 정수로 PARG 인수가 말한다. 이 기능은
** 테스트 중에 사용 된 유일하게 지원 될 필요가 있을 때 SQLITE_TEST
** 이 정의 되어 있습니다.
** <UL>
** <LI> [ SQLITE_FCNTL_SIZE_HINT ]
** [ SQLITE_FCNTL_SIZE_HINT ] opcode가 VFS 를 제공하기 위해 SQLite 에서 사용 되는
** 데이터베이스 파일에있는 성장 하는 크기 의 팁 을 거듭
** 현재 트랜잭션 . 이 팁 은 정확하다는 것을 보장 되지 않지만, 그것은
** 종종 자리 잡고 있습니다. 근저에있는 VFS는 데이터베이스를 미리 하는 것을 선택할지도 모릅니다
** 를 돕기 위해 이 팁 에 따라 파일 공간 은 데이터베이스에 기록
** 파일 의 실행 보다 빠르다.
**
** <LI> [ SQLITE_FCNTL_CHUNK_SIZE ]
** [ SQLITE_FCNTL_CHUNK_SIZE ] opcode를 요청 하는 데 사용 되는 VFS
** 뻗어 있으며, 지정된 크기 의 청크 로 데이터베이스 파일을 자릅니다
** 사용자 에 의한 다. 네 번째 인수 [ sqlite3_file_control 는 ( ) ] 이어야
** 사용하도록 새 청크 크기 를 포함한 정수 ( int 형 ) 을 포인트
** 후보 데이터베이스 . 대규모 데이터베이스 파일 공간을 할당
** 청크 ( 한 번에 1 메가 바이트 라고 ) 파일 시스템 의 단편화를 줄이고 가능성
** 일부 시스템 성능을 향상 시킨다.
**
** <LI> [ SQLITE_FCNTL_FILE_POINTER ]
** [ SQLITE_FCNTL_FILE_POINTER ] opcode가 포인터를 얻기 위해 사용 되는
** 특정 데이터베이스 에 연결된 [ sqlite3_file 개체 에
** 연결 . [ sqlite3_file_control ( ) 문서 를 참조 하십시오.
** 추가 정보 .
**
** <LI> [ SQLITE_FCNTL_SYNC_OMITTED ]
** 사용 되지 않는 . 응
**
** <LI> [ SQLITE_FCNTL_SYNC ]
** [ SQLITE_FCNTL_SYNC ] opcode가 SQLite 의 내부 에서 생성되고
XSYNC 메소드가 호출되기 전에 ** 즉시 VFS 로 전송
** 데이터베이스 파일 기술자 . 또는 XSYNC 메서드가 호출 되지 않은 경우
** 사용자가 에서 SQLite 를 구성 하고 있기 때문에 ,
** [ 프라 그마 동기화 | 프라 그마 동기 = OFF 】 그것이 제자리에 불려
** XSYNC 법 . 대부분의 경우 포인터 인수를 전달 했다고
** 이 파일 제어 는 NULL입니다. 그러나 데이터베이스 파일이 동기화 되는 경우
** 멀티 데이터베이스의 일부로 커밋 널 문자 로 끝나는 인수 포인트
** 거래 마스터 저널 파일 이름을 포함하는 문자열입니다. VFSes 수
** 이 신호를 필요로하지 않는다 조용히 이 opcode가 무시 하십시오. 응용 프로그램
** 이렇게 이 작동 코드 및 ) ( sqlite3_file_control 를 호출 해서는 안됩니다 지도 모른다
** 그것이 필요한 거 전문 VFSes 의 작동 을 중단 시킨다.
**
** <LI> [ SQLITE_FCNTL_COMMIT_PHASETWO ]
** [ SQLITE_FCNTL_COMMIT_PHASETWO ] opcode가 SQLite 에 의해 내부적으로 생성 되는
거래는 즉시 커밋 된 후 ** 와 VFS 에 보내
** 이 데이터베이스 의 잠금이 해제 될 때까지 . 이 신호를 필요로하지 않는다 VFSes
** 침묵 이 opcode가 무시 하십시오. 응용 프로그램에서 호출 해서는 안됩니다
** 이렇게 이 작동 코드 [ sqlite3_file_control 는 ( ) 중단 될 수 있음
** 그것이 필요한 거 전문 VFSes 의 동작을 제어 한다.
**
** <LI> [ SQLITE_FCNTL_WIN32_AV_RETRY ]
** ^ [ SQLITE_FCNTL_WIN32_AV_RETRY ] opcode가 자동 설정 하는 데 사용 되는
용 ** I / O 특정 디스크의 수와 간격 을 다시 시도 운용
** 의 면전에서 견고성을 제공하기 위해 Windows의 VFS ]
** 안티 바이러스 프로그램입니다. 기본적으로 Windows 의 VFS는 파일 의 로드를 다시 시도 합니다
** 파일 쓰기 파일 이 초과되어 10 회 까지 의 작업을 제거
** 25 밀리 세컨드 의 첫 번째 재시도 전에 지연 이 증가했다
** 다음 의 각 시도 에서 추가로 25 밀리 초 . 이
** 작동 코드 가 있습니다 이 두 값 ( 10 재시도 지연 25 밀리 초 )
** 조정 된다. 값은 모든 데이터베이스 연결에 변경됩니다
** 동일한 프로세스에서 . 인수가 2 의 배열에 대한 포인터 이다
** 정수 어디에 새로운 재시도 횟수 I 첫 번째 정수 와 둘째
** 정수 지연 입니다. 두 정수 가 음수이면 설정된 경우
** 변경되지 않지만 설정 하는 것이 아니라 이전 의 값이 써진
** 배열 항목 에 현재 재시도 설정을 할 수 있도록
** 심문 . zDbName 매개 변수는 무시 됩니다.
**
** <LI> [ SQLITE_FCNTL_PERSIST_WAL ]
** ^ [ SQLITE_FCNTL_PERSIST_WAL ] 작동 코드 를 설정하거나 쿼리 하는 데 사용 되는
** 지속 [ WAL | 로그 선행 기입 설정을 . 기본적으로 보조
** 대상 에 쓰기 로그 와 공유 메모리 파일은 트랜잭션 제어 를 위해 사용
** 는 자동으로 제거 될 때 데이터베이스 에 최신 연결
** 닫습니다. 영구 WAL 모드 를 설정하면 해당 파일이 후에도 지속
** 가깝다. 파일 지속성 하면 편리하다 때 없는 다른 프로세스
** 데이터베이스 파일이있는 디렉토리 에 쓰기 권한이 있어야 하고
** WAL 와 공유 메모리 파일로 데이터베이스 파일을 로드하는 데 존재 해야합니다
** 데이터베이스가 읽기 가능 하려면 . 네 번째 매개 변수
** [ sqlite3_file_control ( )이 opcode가 정수에 대한 포인터 이어야 합니다.
** 정수 는 지속 하기 위해 지속적인 WAL 모드 또는 1 을 비활성화 하려면 0 이다
** WAL 모드 . 정수 값이 -1의 경우, 그것은 현재 덮어
** WAL 의 영구 설정 .
**
** <LI> [ SQLITE_FCNTL_POWERSAFE_OVERWRITE ]
** ^ [ SQLITE_FCNTL_POWERSAFE_OVERWRITE ] 작동 코드 를 설정하거나 쿼리 하는 데 사용 되는
** 지속 " powersafe 덮어 "또는 " PSOW " 설정 . PSOW 설정
** 에서 SQLITE_IOCAP_POWERSAFE_OVERWRITE ] 비트 를 결정
** xDeviceCharacteristics 방법 . 네 번째 매개 변수
** [ sqlite3_file_control ( )이 opcode가 정수에 대한 포인터 이어야 합니다.
** 정수 는 제로 손상을 가능하게 하기 위해 제로 손상 모드 또는 1 을 비활성화 하려면 0 이다
** 모드 . 정수 값이 -1의 경우, 그것은 현재 덮어
** 제로 손상 모드 설정 .
**
** <LI> [ SQLITE_FCNTL_OVERWRITE ]
** ^ [ SQLITE_FCNTL_OVERWRITE ] opcode가 개봉 후 SQLite 에 의해 불려갑니다
그것은 일부 에 대한 롤백 하지 않는 한 , ** 쓰기 트랜잭션 은 그것을 설명하기 위해
** 이유, 전체 데이터베이스 파일 은 현재 덮어 씁니다
** 거래. 이것은 VACUUM 조작에 의해 사용 된다.
**
** <LI> [ SQLITE_FCNTL_VFSNAME ]
** ^ [ SQLITE_FCNTL_VFSNAME 】 op 코드 의 이름을 검색하는 데 사용할 수있는
** 모든 [ VFSes ] VFS 스택 . 이름은 모든 VFS 심 것이며,
** 최종 바닥 수준 의 VFS 는 에서 입수 한 메모리 에 기록
** [ sqlite3_malloc ( ) , 그 결과 가 char * 변수에 저장 되어있는
** 및 sqlite3_file_control ( ) 점 의 네 번째 매개 변수 .
** 호출자가 갈 때 메모리를 해제 할 책임이 있습니다. 뿐만 아니라
** 모든 파일 제어 동작이 보증은 없습니다 이 윌 실제로
** 무엇이든 한다. 발신자 은 NULL char * 변수 를 초기화 해야 합니다
** 이 파일 제어 경우 포인터는 구현 되어 있지 않습니다. 이 파일 제어
** 는 진단 만 사용 하기위한 것입니다.
**
** <LI> [ SQLITE_FCNTL_PRAGMA ]
** ^ [ 프라 그마 ] 글이 분석 될 때마다 , SQLITE_FCNTL_PRAGMA ]
** 파일 제어 는 해당 오픈 [ sqlite3_file 개체 에 전송되는
** 데이터베이스 파일 에 프라 그마 문장 이 참조 한다. ^ 인수
** [ SQLITE_FCNTL_PRAGMA ] 파일 제어 의 배열입니다
** 문자열 에 대한 포인터 ( 문자 ** ) 에서 배열 의 두 번째 요소
** 프라 그마 셋째 요소 의 이름은 인수가 함
** 프라 그마 또는 NULL pragma는 인수가없는 경우 . ^ 처리기
** [ SQLITE_FCNTL_PRAGMA ] 파일 제어 가 필요한 첫 번째 요소를 만들 수 있습니다
** CHAR 의 ** 에서 얻은 문자열 인수 포인트 [ ( sqlite3_mprintf )
** 또는 이와 동등한 해당 문자열은 프라 그마 다른 결과 가 될 것이다
** 오류 메시지가 pragma는 실패한 경우 . ^ 만약
** [ SQLITE_FCNTL_PRAGMA ] 파일 제어 가 가기 SQLITE_NOTFOUND 를 선택하고, 일반적인
** [ PRAGMA ] 처리가 계속 됩니다. ^ 만약 [ SQLITE_FCNTL_PRAGMA ]
** 파일 제어 가 돌아 오면 [ SQLITE_OK ] 파서 가정 및
** VFS 프라 그마 자체를 처리 했다고 파서 - OP 를 생성하지 않습니다
** 글을 준비했습니다 . ^ 만약 [ SQLITE_FCNTL_PRAGMA ] 파일 이 반환
** [ SQLITE_OK 또는 SQLITE_NOTFOUND 이외의 결과 코드는 그 수단
** [ 프라 그마 ] 처리 중 VFS는 오류가 발생한 것과
** pragma에 대한 컴파일 오류와 함께 실패 합니다. ^ [ SQLITE_FCNTL_PRAGMA ]
** 파일 제어 는 매우 프라 그마 문장 분석 을 시작할 때 발생 하고
** 그것은 기본 제공 PRAGMA ] 문장 을 덮어 쓸 수 있습니다.
**
** <LI> [ SQLITE_FCNTL_BUSYHANDLER ]
** ^ [ SQLITE_FCNTL_BUSYHANDLER ]
** 파일 제어 데이터베이스 의 파일 핸들 은 SQLite 에서 호출 할 수있는
** 이것은 액세스 사용자 지정 VFS 를 제공하기 위해 열린 직후 에
** 연결 바쁜 처리기 콜백 에 . 인수가 타입 이다 ( 비활성화 ** )
** - 2 (무효 * ) 값 의 배열입니다. 첫 번째 (무효 * ) 실제 포인트
** 유형 ( INT ( * ) (무효 * ) ) 기능 . 연결을 호출하는 데
** 바쁜 처리기는이 함수는 두 번째 (무효 * ) 를 사용하여 시작 해야 합니다
** 유일한 인수로 배열입니다. 그것은 제로 하지 않으면 작업이 반환 된 경우
** 다시 시도 해야 합니다. 그것은 제로 를 반환하면 사용자 지정 VFS 이 포기해야 할
** 현재 작업 .
**
** <LI> [ SQLITE_FCNTL_TEMPFILENAME ]
** ^ 응용 [ SQLITE_FCNTL_TEMPFILENAME ] 파일 제어 를 호출 할 수 있습니다
** SQLite 를 갖게 하면 생성
생성 에 이어 것과 동일한 알고리즘을 사용하여 ** 임시 파일 이름
임시 테이블 등 의 내부 사용을 위해 ** 임시 파일 이름 . 더
** 인수가 파일명 으로 채우는 것이다 ** CHAR 해야 합니다
** [ sqlite3_malloc ( ) 에서 가져온 메모리 에 기록합니다. 호출자가 해야
** 메모리 누수 를 피하기 위해, 그 결과 에 [ sqlite3_free 을 ( ) 를 호출합니다.
**
** <LI> [ SQLITE_FCNTL_MMAP_SIZE ]
** [ SQLITE_FCNTL_MMAP_SIZE ] 파일 제어 는 조회 또는 설정 하는 데 사용 되는
** 메모리 맵 I / O 에 사용되는 최대 바이트 수
** 인수는 유형 sqlite3_int64 값 에 대한 포인터 이다
** 메모리 맵 파일 의 바이트 자문 최대 이다. 더
** 포인터가 이전 값으로 덮어 됩니다. 제한이 변경 되지 않은 경우
** 값이 원래 조준 음이고 , 그래서 전류 제한
** 음수 에 대한 포인터를 전달하여 조회 할 수 있습니다. 이
** 파일 제어 [ 프라 그마 mmap_size 을 구현 하기 위해 내부적으로 사용 됩니다.
**
** <LI> [ SQLITE_FCNTL_TRACE ]
** [ SQLITE_FCNTL_TRACE ] 파일 제어 는 통보 정보를 제공 합니다
** SQLite는 스택의 상위 계층 이 무엇을 하고 있는지 에 대한 VFS 에 .
** 이 파일 제어 [ 심 ] 추적 일부 VFS 의 활동에 의해 사용 됩니다.
** 인수가 제로 로 끝나는 문자열 입니다. 중상 위 계층
** SQLite 의 스택 이 파일 컨트롤 의 인스턴스를 생성 할 가능성 이있는 경우
** [ SQLITE_USE_FCNTL_TRACE ] 컴파일 시 옵션이 활성화되어 있습니다.
**
** <LI> [ SQLITE_FCNTL_HAS_MOVED ]
** [ SQLITE_FCNTL_HAS_MOVED ] 파일 제어 와 같이 인수를 해석 할
** 정수에 대한 포인터 에서 그것을 그 정수 에 부울 값을 씁니다 만 의존
파일 의 이름이 변경 되었다. ** 에 여부 에 관계없이 이동 또는 이후 에 삭제
** 먼저 열렸습니다 .
**
** < / UL >
* /
#define SQLITE_FCNTL_LOCKSTATE               1
#define SQLITE_GET_LOCKPROXYFILE             2
#define SQLITE_SET_LOCKPROXYFILE             3
#define SQLITE_LAST_ERRNO                    4
#define SQLITE_FCNTL_SIZE_HINT               5
#define SQLITE_FCNTL_CHUNK_SIZE              6
#define SQLITE_FCNTL_FILE_POINTER            7
#define SQLITE_FCNTL_SYNC_OMITTED            8
#define SQLITE_FCNTL_WIN32_AV_RETRY          9
#define SQLITE_FCNTL_PERSIST_WAL            10
#define SQLITE_FCNTL_OVERWRITE              11
#define SQLITE_FCNTL_VFSNAME                12
#define SQLITE_FCNTL_POWERSAFE_OVERWRITE    13
#define SQLITE_FCNTL_PRAGMA                 14
#define SQLITE_FCNTL_BUSYHANDLER            15
#define SQLITE_FCNTL_TEMPFILENAME           16
#define SQLITE_FCNTL_MMAP_SIZE              18
#define SQLITE_FCNTL_TRACE                  19
#define SQLITE_FCNTL_HAS_MOVED              20
#define SQLITE_FCNTL_SYNC                   21
#define SQLITE_FCNTL_COMMIT_PHASETWO        22

/ * 
** CAPI3REF : 뮤텍스 핸들 
** 
** SQLite의 내부 뮤텍스 모듈은 [sqlite3_mutex 및 정의하고 
** 뮤텍스 오브젝트의 추상 타입. SQLite 코어가 보이는 것은 없습니다 
** [sqlite3_mutex]의 내부 표현. 그냥 
** [sqlite3_mutex 개체에 대한 포인터를 다룬다. 
** 
** 뮤텍스는 [sqlite3_mutex_alloc를 ()를 사용하여 만들어집니다. 
* /
typedef struct sqlite3_mutex sqlite3_mutex;
/ *
** CAPI3REF : OS 의 인터페이스 오브젝트
**
** sqlite3_vfs 개체 의 인스턴스 사이 의 인터페이스를 정의
** SQLite 코어와 기본 운영 시스템 . " VFS "
** 개체 의 이름 에 " 가상 파일 시스템 " 의 약자입니다. 보기
** | 자세한 내용은 VFS VFS 의 문서 .
**
** IVERSION 필드 의 값은 처음에는 1 이지만 클 수 있었다
SQLite 의 ** 이후 버전 . 추가 필드 는 이것에 추가 할 수있다
** IVERSION 값 이 증가하고 있는 객체입니다. 그러나 구조
** 트랜잭션 sqlite3_vfs 개체의 수정 사이
** SQLite 버전 3.5.9 및 3.6.0 와 아직 IVERSION 필드가 없습니다
** 수정.
**
** szOsFile 필드를 서브 클래 싱 된 [ sqlite3_file ] 크기 이다
** 이 VFS 에서 사용되는 구조. mxPathname 최대 길이 이다
** 이 VFS 에 경로 이름.
**
** 등록 sqlite3_vfs 개체 에 의해 형성된 링크 목록 에 유지됩니다
** pNext 포인터 . [ sqlite3_vfs_register ( )
** 및 sqlite3_vfs_unregister ( ) 인터페이스는 이 목록 관리
** 스레드 로부터 안전한 방식으로 . [ sqlite3_vfs_find ( ) 인터페이스
** 목록 을 검색 합니다. 응용 프로그램 코드 에서도 VFS 아닌
** 구현 pNext 포인터를 사용 해야 합니다.
**
** pNext 필드 는 sqlite3_vfs 에서 유일한 필드 이다
** SQLite 는 지금 까지 변경됩니다 구조. SQLite 는 의지 전용 액세스
특정 정적 뮤텍스를 유지 하고있는 동안 ** 또는 이 필드 를 변경합니다.
** 응용 프로그램이 sqlite3_vfs 이내 아무것도 변경 하지 마십시오
** 개체가 등록 된 개체 일단 .
**
** ZNAME 필드 는 VFS 모듈 의 이름을 유지합니다. 이름 필수
** 모든 VFS 모듈 전체에서 고유 이다.
**
** [ sqlite3_vfs.xOpen ]
** ^ SQLite 는 보장 XOPEN 에 zFilename 매개 변수
** NULL 포인터 나 문자열 을 얻을
** xFullPathname 에서 ( ) 옵션 의 접미사 가 추가 되었습니다 .
** ^ 접미사가 zFilename 매개 변수 에 추가 되는 경우 의지
" - " 에 불과하지만 오는 문자 ** 싱글로 구성되어
** 11 영숫자 및 / 또는 "-" 문자 .
** ^ SQLite는 더욱 보장 할
XCLOSE 는 ( )까지 ** 문자열 은 유효하며, 변경되지 않습니다
** 라고. 이전 글 때문에,
** [ sqlite3_file ] 안전 에 대한 포인터를 저장 할 수 있습니다
** 그것이 어떤 이유로 파일 이름 을 기억할 필요 가있는 경우 파일 이름 .
** XOPEN 에 zFilename 매개 변수가 다음 XOPEN NULL 포인터 의 경우
** 파일 에 자신의 임시 이름 을 고안 해야 한다. ^ 언제든지
** xFilename 매개 변수는 그것도 케이스가되는 null 인 것을
** flags 매개 변수 는 [ SQLITE_OPEN_DELETEONCLOSE ] 가 포함됩니다.
**
** XOPEN ( ) 의 flags 인수는 에 설정되어 있는 모든 비트 를 포함
** [ sqlite3_open_v2 ( ) 의 flags 인수 . 하거나 [에서 sqlite3_open ( )
** 또는 sqlite3_open16 ( )가 사용 된 다음 의 플래그는 적어도
** [ SQLITE_OPEN_READWRITE ] | [ SQLITE_OPEN_CREATE ] .
XOPEN ( ) 는 파일을 열 경우 **, 읽기 전용 ,에 * pOutFlags 을 설정
** [ SQLITE_OPEN_READONLY ] 가 포함된다. * pOutFlags 다른 비트 를 설정할 수 있다.
**
** ^ ( SQLite 는 또한 XOPEN 다음 플래그 중 하나를 추가 ( ) 합니다
** 열려있는 개체 에 따라 호출합니다.
**
** <UL>
** <LI> [ SQLITE_OPEN_MAIN_DB ]
** <LI> [ SQLITE_OPEN_MAIN_JOURNAL ]
** <LI> [ SQLITE_OPEN_TEMP_DB ]
** <LI> [ SQLITE_OPEN_TEMP_JOURNAL ]
** <LI> [ SQLITE_OPEN_TRANSIENT_DB ]
** <LI> [ SQLITE_OPEN_SUBJOURNAL ]
** <LI> [ SQLITE_OPEN_MASTER_JOURNAL ]
** <LI> [ SQLITE_OPEN_WAL ]
** < / UL > ) ^
**
** 파일 I / O 의 구현은 개체 형식 의 플래그를 다음과 같이 사용할 수 있습니다
** 그것은 파일을 취급하는 방법 을 변경 한다. 예를 들어, 응용 프로그램
** 그것이 충돌 복구 를 신경 쓰지 않거나 롤백 이 될지도 모른다
** 저널 파일 무 조작 의 오픈. 이 잡지 에 쓸 것이다
** 도 하늘 명령도 없이 잡지 를 읽고 하려고 하면 돌아올
** SQLITE_IOERR . 또는 구현이 인식 할 수있는 데이터베이스
** 파일 은 페이지 경계 섹터 될 것이다 읽기 와 무작위로 쓰고있다
** 주문 하고 그에 따라 I / O 서브 시스템 을 설정합니다.
**
** SQLite 는 또한 XOPEN 메서드에 다음 플래그 의 1 을 추가 할 수 있습니다 .
**
** <UL>
** <LI> [ SQLITE_OPEN_DELETEONCLOSE ]
** <LI> [ SQLITE_OPEN_EXCLUSIVE ]
** < / UL >
**
** [ SQLITE_OPEN_DELETEONCLOSE 플래그 는 파일 이 있어야 한다는 것을 의미
그것이 닫혀 있다면 ** 삭제 . ^ [ SQLITE_OPEN_DELETEONCLOSE ]
** 과도 , TEMP 데이터베이스와 잡지를 위해 설정됩니다
** 데이터베이스 subjournals .
**
** ^ [ SQLITE_OPEN_EXCLUSIVE 플래그 는 항상 함께 사용 되는
** [ SQLITE_OPEN_CREATE 플래그 와 직접적인 이다
** POSIX 오픈 O_EXCL 과 O_CREAT 플래그 와 유사 ( )
** API입니다. SQLITE_OPEN_EXCLUSIVE 플래그 와 대
** SQLITE_OPEN_CREATE 가 만일 항상 파일을 나타내는 데 사용 되는
** 만들어지고 그것이 이미 존재하는 경우는 에러가된다.
** 이것은 <I> 가 < / i > 은 파일을 나타내는 데 사용 열리는 것이지 없습니다
** 독점 액세스 를 위해 .
**
** ^ 메모리 의 적어도 szOsFile 바이트 는 SQLite 때문에 할당 된
** 유지 셋째 로 전달 된 [ sqlite3_file ] 구조
** XOPEN 인수 . XOPEN 메서드가 필요하지 않습니다
** 구조체 를 할당하고 그냥 참고 인치 동의를 위탁해야한다
** XOPEN 법 은 sqlite3_file.pMethods 을 다음과 같이 설정 해야 한다 중 하나
** 유효한 [ sqlite3_io_methods 개체 이거나 NULL . XOPEN 을 해야 합니다.
** 여는 데 실패 했다. 이 경우 도 마찬가지입니다. SQLite 는 기대하고 있는지 sqlite3_file.pMethods
XOPEN 성공 에 관계없이 돌아온 후 ** 요소가 활성화됩니다
** 또는 XOPEN 호출 실패.
**
** [ sqlite3_vfs.xAccess ]
** ^ Xaccess 위하여 flags 인수는 ( ) [ SQLITE_ACCESS_EXISTS ] 수
** 에 [ SQLITE_ACCESS_READWRITE ] 파일 이 있는지 여부를 테스트 또는 그것에
** 테스트 파일 을 읽고 쓸 수 있는지 , SQLITE_ACCESS_READ ] 또는
** 파일은 적어도 읽을 수 있는지 여부를 테스트 한다. 파일은 수 있습니다
** 디렉토리 .
**
** ^ SQLite 는 항상 적어도 mxPathname 위한 1 바이트를 할당
** 출력 버퍼 xFullPathname . 출력 버퍼 의 정확한 크기
** 두 메서드 에 매개 변수로 전달됩니다. 만약 출력 버퍼
** 충분한 크기 에서 SQLITE_CANTOPEN ] 반환 되어야 하지 않습니다. 이것이 있으니까
** 의 SQLite 에 의한 치명적인 오류로 처리, VFS 구현 노력해야한다
** 충분히 큰 값으로 mxPathname 을 설정하여 이를 방지하기 위해.
**
** xRandomness ( ) xSleep ( ) xCurrentTime ( ) 및 xCurrentTimeInt64 ( )
** 인터페이스는 파일 시스템 의 정확한 일부가 아니지만, 그들은 있다
** 완전성 VFS 구조 에 포함된다.
** xRandomness ( ) 함수는 n 바이트 의 바이트 를 돌려 주려고
** ZOUT 에 상질의 임의성 . 반환 값은
** 여행 임의성 의 실제 바이트 수입니다.
** xSleep ( ) 메서드는 호출 스레드 가 나오기 를 중지합니다
** 적어도 마이크로 초 는 지정 되었다. ^ xCurrentTime ( )
** 메서드는 현재 날짜와 시간 에 대한 율리우스 날짜 를 반환합니다.
** 부동 소수점 값입니다.
** ^ xCurrentTimeInt64 ( ) 메소드가 복귀 정수, 줄리안 등
** 일 밀리 초 ( 숫자 86400000 를 걸어
** 1 일 24 시간 ) .
** ^ SQLite 는 전류를 얻기 위해 xCurrentTimeInt64 ( ) 메서드를 사용 합니다
그 방법 이 제공 되고 있습니다 ** 날짜와 시간 의 경우 는 ( IVERSION 2 일
** 크고, 함수 포인터가 NULL이 아닌 ) 로 대체 합니다
** xCurrentTime 에 ( ) xCurrentTimeInt64 ( ) 를 사용할 수없는 경우 .
**
** ^ xSetSystemCall ( ) xGetSystemCall ( ) 및 xNestSystemCall ( ) 인터페이스
** SQLite 코어 는 사용 되지 않습니다 . 이러한 옵션 의 인터페이스 가 포함되어 있습니다
** 일부 VFSes 의해 VFS 코드 의 테스트를 용이하게 한다. 재정의 함으로써
** 시스템은 시험 프로그램이 있어 그 제어하는 기능을 호출
** 시뮬레이션 장애, 그렇지 않으면 곤란하다 오류 조건
** 또는 유도 하는 것은 불가능하다. 재정의 할 수있는 시스템 호출 세트
** 1 VFS 에서 또 다른 다르지만 동일한 VFS 의 1 버전에서
** 다음 . 이러한 인터페이스를 사용하는 응용 프로그램 중 하나 를 위해 준비 해야 합니다
** 또는 이러한 인터페이스는 모두 NULL 또는 변경 에 그들의 행동 을 위해 해야
** 1 릴리스 에서 다음 . 응용 프로그램 에 액세스 하지 마십시오
**이 방법 중 하나 VFS 의 IVERSION 이 3 미만인 경우 .
* /
typedef struct sqlite3_vfs sqlite3_vfs;
typedef void (*sqlite3_syscall_ptr)(void);
struct sqlite3_vfs {
  int iVersion;            /* Structure version number (currently 3) */
  int szOsFile;            /* Size of subclassed sqlite3_file */
  int mxPathname;          /* Maximum file pathname length */
  sqlite3_vfs *pNext;      /* Next registered VFS */
  const char *zName;       /* Name of this virtual file system */
  void *pAppData;          /* Pointer to application-specific data */
  int (*xOpen)(sqlite3_vfs*, const char *zName, sqlite3_file*,
               int flags, int *pOutFlags);
  int (*xDelete)(sqlite3_vfs*, const char *zName, int syncDir);
  int (*xAccess)(sqlite3_vfs*, const char *zName, int flags, int *pResOut);
  int (*xFullPathname)(sqlite3_vfs*, const char *zName, int nOut, char *zOut);
  void *(*xDlOpen)(sqlite3_vfs*, const char *zFilename);
  void (*xDlError)(sqlite3_vfs*, int nByte, char *zErrMsg);
  void (*(*xDlSym)(sqlite3_vfs*,void*, const char *zSymbol))(void);
  void (*xDlClose)(sqlite3_vfs*, void*);
  int (*xRandomness)(sqlite3_vfs*, int nByte, char *zOut);
  int (*xSleep)(sqlite3_vfs*, int microseconds);
  int (*xCurrentTime)(sqlite3_vfs*, double*);
  int (*xGetLastError)(sqlite3_vfs*, int, char *);
  /*
  ** The methods above are in version 1 of the sqlite_vfs object
  ** definition.  Those that follow are added in version 2 or later
  */
  int (*xCurrentTimeInt64)(sqlite3_vfs*, sqlite3_int64*);
  /*
  ** The methods above are in versions 1 and 2 of the sqlite_vfs object.
  ** Those below are for version 3 and greater.
  */
  int (*xSetSystemCall)(sqlite3_vfs*, const char *zName, sqlite3_syscall_ptr);
  sqlite3_syscall_ptr (*xGetSystemCall)(sqlite3_vfs*, const char *zName);
  const char *(*xNextSystemCall)(sqlite3_vfs*, const char *zName);
  /*
  ** The methods above are in versions 1 through 3 of the sqlite_vfs object.
  ** New fields may be appended in figure versions.  The iVersion
  ** value will increment whenever this happens. 
  */
};

/ *
** CAPI3REF : Xaccess 의 VFS 법 의 플래그
**
**이 정수 는 세 번째 매개 변수 로 사용할 수 있습니다
** [ sqlite3_vfs 개체 의 Xaccess 방법 . 그들은 결정
** Xaccess 방법 이 찾고있는 권한 종류.
** SQLITE_ACCESS_EXISTS 에서 Xaccess 방법
** 단순히 파일 이 존재하는지 여부를 확인합니다.
** SQLITE_ACCESS_READWRITE , Xaccess 방법은
라는 디렉터리 가 읽기 및 쓰기 인지 여부를 확인 한다. **
** ( 파일을 추가 할 경우 , 즉, 제거 하고 안에 개명
** 디렉토리 ) .
** SQLITE_ACCESS_READWRITE 상수 는 현재 에 사용 되는
** [ temp_store_directory 프라 그마 , 이것은 장래 변경 될 가능성 이 있지만
** SQLite는 릴리스 .
** SQLITE_ACCESS_READ , Xaccess 방법은
** 파일 을 읽을 수 있는지 여부를 확인합니다. SQLITE_ACCESS_READ 상수 이다
** 현재 사용 되지 않습니다, 그것은 릴리스에서 사용 할 수 있습니다 만
** SQLite는 .
* /
#define SQLITE_ACCESS_EXISTS    0
#define SQLITE_ACCESS_READWRITE 1   /* Used by PRAGMA temp_store_directory */
#define SQLITE_ACCESS_READ      2   /* Unused */

/ * 
** CAPI3REF : xShmLock VFS 법의 플래그 
** 
**이 정수는 다른 잠금 작업을 정의하는 
** [sqlite3_io_methods]의 xShmLock 법이 허용되고있다. 더 
** 다음 플래그의 유일한 합법 조합 
** xShmLock 방법 : 
** 
** <UL> 
** <LI>의 SQLITE_SHM_LOCK | SQLITE_SHM_SHARED 
** <LI>의 SQLITE_SHM_LOCK | SQLITE_SHM_EXCLUSIVE 
** <LI>의 SQLITE_SHM_UNLOCK | SQLITE_SHM_SHARED 
** <LI>의 SQLITE_SHM_UNLOCK | SQLITE_SHM_EXCLUSIVE 
** </ UL> 
** 
잠금 해제 한 경우 ** 같은 공유 또는 배타적 플래그로 공급되어야한다 
** 해당 잠금을 받았다. 
** 
** xShmLock 메서드는 잠금 해제와 공유하거나 사이를 전환 할 수 있습니다 
** 잠금 해제와 독점적 사이. 그것은 공유 사이에서 마이그레이션 할 수 없습니다 
**와 배타. 
* /
#define SQLITE_SHM_UNLOCK       1
#define SQLITE_SHM_LOCK         2
#define SQLITE_SHM_SHARED       4
#define SQLITE_SHM_EXCLUSIVE    8

/ * 
** CAPI3REF : 최대 xShmLock 지수 
** 
** [sqlite3_io_methods] 위 xShmLock 메서드가 값을 사용하여도된다 
** 0로이 제한을 사이에 인수를 "오프셋" 
** SQLite의 핵심은 검색하거나 해제하지 마십시오합니다 
**이 범위를 벗어나 록 
* /
#define SQLITE_SHM_NLOCK        8


/ *
** CAPI3REF : SQLite 라이브러리를 초기화합니다
**
** ^ sqlite3_initialize ( ) 루틴은 초기화
** SQLite 라이브러리 . ^ sqlite3_shutdown ( ) 루틴
** ( ) sqlite3_initialize 의해 할당 된 모든 리소스를 해제 합니다.
**이 루틴은 프로세스 의 초기화 를 지원 하도록 설계 되어 있다
** 임베디드 시스템 종료 . 사용한 워크 스테이션 애플리케이션
** SQLite 는 일반적으로 이러한 루틴 중 하나를 시작할 필요가 없습니다.
**
그 경우 ** ( sqlite3_initialize 호출 ) 가 '유효' 호출 입니다
** 처음 sqlite3_initialize 는 ( ) 의 유효 기간 중에 불려
그것이 처음이다 sqlite3_initialize ** 프로세스 또는 ( )가 불려
** sqlite3_shutdown 호출 을 다음 ( ) . ^ ( 실효 통화 만
** sqlite3_initialize 의 ( ) 초기화 합니다. 다른 모든 통화
** 무해 하늘 명령어는 없습니다. ) ^
**
그것은 처음 에있는 경우 ** ( sqlite3_shutdown 호출 ) 가 '유효' 호출 입니다
** ) ( 마지막 sqlite3_initialize 이상 ( ) sqlite3_shutdown 하기 위해 호출한다. ^ (단
** sqlite3_shutdown 하기위한 효과적인 ( ) 를 호출하면 모든 초기화 해제 합니다.
** 다른 모든 유효한 호출 ) 가 NO - OPS 무해하다 ( sqlite3_shutdown 한다. ) ^
**
** sqlite3_initialize ( ) 인터페이스는 thread 세이프입니다 만 , sqlite3_shutdown ( )
** 가 없습니다. sqlite3_shutdown ( ) 인터페이스에서만 호출 되어야 한다
** 단일 스레드 . 열려있는 모든 데이터베이스 연결 은 닫히고 모든 해야 한다
** 다른 SQLite는 자원이 이전 호출 에 할당 을 해제 해야 합니다
** sqlite3_shutdown ( ) .
**
** 특히, ^ sqlite3_initialize ( ) 가 호출됩니다
** sqlite3_os_init ( ) . 마찬가지로 ^ sqlite3_shutdown ( )
** ) ( sqlite3_os_end 를 호출합니다.
**
** ^ sqlite3_initialize ( ) 은 성공 반품 [ SQLITE_OK ] .
** ^ 어떤 이유로, sqlite3_initialize ( ) 의 경우 는 초기화 할 수 없습니다
** 라이브러리 ( 아마 그런 필요한 리소스를 할당 할 수 없다
** 뮤텍스 로 ) 그것은 [ SQLITE_OK 이외의 오류 코드 를 돌려줍니다.
**
** ^ sqlite3_initialize ( ) 루틴은 다른 많은 의해 내부에서 불려갑니다
** SQLite 인터페이스는 응용 프로그램이 일반적으로 필요하지 않습니다 처럼
** 직접 ( ) sqlite3_initialize 를 호출합니다. 예를 들어, 에서 sqlite3_open ( )
** sqlite3_initialize ( ) 를 호출 하기 때문에, SQLite 라이브러리 는 자동으로 됩니다
** 그것이 초기화되지 않은 경우 에 sqlite3_open 는 ( ) 가 호출 될 때 초기화
** 이미 . ^ 하지만 SQLite 는 [ SQLITE_OMIT_AUTOINIT 에서 컴파일 된 경우
** 컴파일 시 옵션 자동 호출 sqlite3_initialize 합니다 ( )
** 생략 된 응용 프로그램이 직접 ) ( sqlite3_initialize 를 호출 해야합니다
** 다른 SQLite 인터페이스를 사용 하기 전에. 이식성을 최대화하기 위해 ,
** 그것은 응용 프로그램이 항상 sqlite3_initialize 를 호출하는 것을 추천 합니다 ( )
** 다른 SQLite 인터페이스를 사용하여 사전 에 직접. 이후 릴리스
** SQLite 의 이를 필요로하는 경우가 있습니다. 즉, 동작이 출전
** SQLite 는 [ SQLITE_OMIT_AUTOINIT 을 사용하여 컴파일 된 때에는 될지도 모른다
** SQLite 의 일부 릴리스 에서는 기본 동작 .
**
** sqlite3_os_init ( ) 루틴은 운영 체제 고유 의 것
** SQLite 라이브러리 의 초기화 . sqlite3_os_end ( )
** 루틴이 sqlite3_os_init 의 효과를 되돌립니다 ( ) . 일반적인 작업
**이 루틴이 실행 되려면 할당 또는 할당 해제 를 포함
** 정적 리소스 글로벌 변수 의 초기화
** 기본 [ sqlite3_vfs 모듈을 설정 또는 설정
** 사용하여 기본 설정 sqlite3_config 을 ( ) .
**
** 응용 프로그램이 sqlite3_os_init ( ) 중 하나를 호출 하지 않습니다
** 또는 sqlite3_os_end ( ) 를 직접. 응용 프로그램은 시작 해야 합니다
** sqlite3_initialize ( ) 와 sqlite3_shutdown ( ) . sqlite3_os_init ( )
** 인터페이스 ) ( sqlite3_initialize 에 의해 자동으로 호출되어
** sqlite3_os_end 은 ( ) ) sqlite3_shutdown ( 에 의해 호출됩니다. 적절한
** sqlite3_os_init 구현 ( ) 와 sqlite3_os_end ( )
그것은 Unix 및 Windows 또는 OS / 2 용으로 컴파일 된 경우 ** 는 SQLite 에 포함되어 있습니다.
** 사용자 지정 빌드 | 다른 플랫폼 에 구축 된 ] 때
** ( 사용하여 SQLITE_OS_OTHER = 1 ] 컴파일 시
** 옵션 ) 응용 프로그램은 적합한 구현을 제공 해야 합니다
** sqlite3_os_init ( ) 와 sqlite3_os_end ( ) . 응용 프로그램 제공
** sqlite3_os_init ( ) 의 구현 또는 sqlite3_os_end ( )
** 반환 해야한다 [ SQLITE_OK ] 성공과 다른 몇 가지 오류 코드 ] 시
** 실패 .
* /
SQLITE_API int sqlite3_initialize(void);
SQLITE_API int sqlite3_shutdown(void);
SQLITE_API int sqlite3_os_init(void);
SQLITE_API int sqlite3_os_end(void);

/ *
** CAPI3REF : 설정 더 SQLite 라이브러리
**
** sqlite3_config ( ) 인터페이스는 글로벌 구성 을 위해 사용 되는
** 의 특정 요구에 튜닝 하는 SQLite 의 순서 에서 SQLite 의 변경
** 응용 프로그램 . 기본 설정은 대부분 것을 권장합니다
** 응용 프로그램 때문에 이 루틴 은 일반적으로 필요하지 않습니다. 그것은
** 특별한 요구를 가진 희귀 응용 프로그램을 지원하기 위해 제공 했다.
**
** sqlite3_config ( ) 인터페이스는 스레드로부터 안전 하지 않습니다. 응용 프로그램
** 다른 SQLite 의 인터페이스는 다른 것으로 호출되지 않도록 해야 한다
** 스레드 sqlite3_config ( ) 가 실행되고 있는 동안. 또한 sqlite3_config ( )
** 에만 사용 하는 레거시 라이브러리 의 초기화 호출 할 수
** [ sqlite3_initialize ( ) 또는 sqlite3_shutdown ( ) 종료 이후 .
** ^ sqlite3_config 는 ( ) [ sqlite3_initialize ( ) ] 후 와 전에 불려 갔을 경우
** [ sqlite3_shutdown ( ) ] 그것은 SQLITE_MISUSE 가 반환됩니다.
** 주의 그러나 ^ sqlite3_config 는 ( ) 의 일부로 호출 할 수 있습니다
** 응용 프로그램 정의 의 구현 [ sqlite3_os_init ( ) .
**
** ) ( sqlite3_config 의 첫 번째 인수는 정수입니다
** 설정 옵션을 결정하는
** SQLite는 어떤 특성 으로 구성 된다. 이후의 인수
** 설정 옵션 에 따라 변화하는
** 첫 번째 인수 .
**
** ^ 구성 옵션 이 설정되어 있는 sqlite3_config ( ) 가 반환 [ SQLITE_OK ] .
** ^ 옵션이 없거나 , SQLite 는 옵션을 설정할 수없는 경우
** 이 루틴 은 0이 아닌 오류 코드 를 반환합니다.
* /
SQLITE_API int sqlite3_config(int, ...);

/ * 
** CAPI3REF 구성 : 데이터베이스 연결 
** 
** sqlite3_db_config () 인터페이스는 구성하는 데 사용되는 
** 데이터베이스 연결로 변경. 인터페이스는 다음과 같습니다. 
** [sqlite3_config ()의 변경을 단일에 적용되는 것을 제외하고, 
** (첫번째 인수로 지정된) 데이터베이스 연결. 
** 
** (D, V, ...)을 sqlite3_db_config2 번째 인수가 
** [SQLITE_DBCONFIG_LOOKASIDE | 피규 동사 - 정수 코드 
** 즉, 데이터베이스 연결 화면이 설정되어 있는지를 나타냅니다. 
** 이후의 인수는 설정 동사에 따라 다릅니다. 
** 
** ^ 경우에만 ()의 반환 SQLITE_OK을 sqlite3_db_config 호출 
** 호출이 성공했다고 간주됩니다. 
* /
SQLITE_API int sqlite3_db_config(sqlite3*, int op, ...);
/ *
** CAPI3REF : 메모리 할당 루틴
**
** 이 개체의 인스턴스 는 SQLite 사이 의 인터페이스를 정의
** 및 낮은 수준의 메모리 할당 루틴 .
**
** 이 개체는 SQLite 인터페이스 에서 유일한 장소 사용되고 있습니다.
** 이 개체의 인스턴스 에 대한 포인터 인수가
** [ sqlite3_config ( ) 설정 옵션 의 경우
** [ SQLITE_CONFIG_MALLOC 또는 SQLITE_CONFIG_GETMALLOC ] .
** 이 개체 의 인스턴스를 만듭니다
** 및 sqlite3_config 로 전달 ( SQLITE_CONFIG_MALLOC ] )
** 구성 할 때 응용 프로그램 은 대안을 지정할 수 있습니다
** SQLite 를위한 메모리 할당 하위 시스템은 모든 사용
** 동적 메모리 가 필요하다.
**
** SQLite 는 몇 가지 포함되어 있습니다 점에 유의 하십시오 [ 내장 메모리 할당 ]
** 응용 프로그램 의 대다수 에 완전히 적합하다
** 이 개체는 응용 프로그램 의 극히 소수 에만 유용하다는 것을
** 특수 메모리 할당 요구 사항. 이 개체는 있다
** 대체 를 지정 하기 위해 SQLite 의 테스트 동안 사용
메모리 메모리 부족 상태 를 시뮬레이션 ** 메모리 할당
** 그 SQLite 를 확인하기 위해 더 우아하게 복구
** 조건.
**
** xMalloc , xRealloc , 그리고 XFree 방법은 다음과 같이 작동 해야 합니다
** 의 malloc ( ) , realloc 의 ( ) 과 표준 C 라이브러리 에서 무료로 ( ) 함수 .
** ^ SQLite 는 보증 과 둘째 인수
** xRealloc 항상 xRoundup 이전 호출에서 반환 된 값입니다.
**
** XSIZE 메모리 할당 의 할당 된 크기를 반환해야 합니다
** 이전 xMalloc 또는 xRealloc 에서 가져 . 할당 된 크기
** 항상 요청 된 크기와 최소한 같은 크기 이지만, 크고 있다.
**
** xRoundup 방법은 할당 된 크기 가되는지를 돌려줍니다
** 메모리 할당 은 특정 요구 된 크기를 줬다. 대부분의 메모리
** 할당 은 최소한 다음 의 배수로 메모리 할당을 올림
** 8. 일부 할당 은 더 큰 배수 또는 2 의 거듭 제곱 으로 반올림 .
** 에서 들어오는 모든 메모리 할당 요청 [ sqlite3_malloc ( )
** 또는 sqlite3_realloc ( ) 제 xRoundup 를 호출합니다. xRoundup 는 0을 반환하고 경우
** 그것은 해당 메모리 할당 이 실패합니다.
**
** xinit 방법은 메모리 할당 을 초기화 합니다. 예를 들어,
** 이것은 어떤 뮤텍스를 요구하는 할당하거나 내부 데이터 를 초기화 할 수 있습니다
** 구조. xShutdown 법 에 의해 ( 간접적으로 ) 호출
** [ sqlite3_shutdown ( ) 가져온 모든 리소스를 해제 해야 합니다
** XINIT 에 따른다. pAppData 포인터 는 유일한 매개 변수 로 사용 되는
** XINIT 과 xShutdown .
**
그것이 시작할 때 ** SQLite 는 [ SQLITE_MUTEX_STATIC_MASTER ] 뮤텍스를 보유하고있는
** xinit 방법 이므로, xinit 의 메소드는 thread 세이프 일 필요는 없습니다. 더
** xShutdown 방법은 [ sqlite3_shutdown ( ) 에서 호출되므로 그것은 아닙니다 된
** 어느 스레드로부터 안전 필요하지 . 다른 모든 메서드 SQLite 를위한
** 한 [ SQLITE_MUTEX_STATIC_MEM ] 뮤텍스를 보유하고있는
** [ SQLITE_CONFIG_MEMSTATUS 설정 옵션 ( 선택되어 있는
** 이것은 디폴트 이다 ) 등 의 메서드는 자동으로 직렬화 됩니다.
[ SQLITE_CONFIG_MEMSTATUS 이 비활성화 되어있는 경우 ** 하지만 다른
** 메서드는 스레드로부터 안전 하거나 다른 독자적인 어레인지 용 을 해야 한다
** 연재.
**
** SQLite 는 개입 하지 않고 여러 번 ) 더 ( XINIT 를 호출 하지 않습니다
** ) ( xShutdown 호출합니다.
* /
typedef struct sqlite3_mem_methods sqlite3_mem_methods;
struct sqlite3_mem_methods {
  void *(*xMalloc)(int);         /* Memory allocation function */
  void (*xFree)(void*);          /* Free a prior allocation */
  void *(*xRealloc)(void*,int);  /* Resize an allocation */
  int (*xSize)(void*);           /* Return the size of an allocation */
  int (*xRoundup)(int);          /* Round up request size to allocation size */
  int (*xInit)(void*);           /* Initialize the memory allocator */
  void (*xShutdown)(void*);      /* Deinitialize the memory allocator */
  void *pAppData;                /* Argument to xInit() and xShutdown() */
};

/ *
** CAPI3REF : 설정 옵션
** KEYWORDS : { 옵션 }
**
**이 상수는 사용할 수있는 정수 의 설정 옵션 임을
** [ sqlite3_config ( ) 인터페이스 의 첫 번째 인수로 전달할 수 있습니다.
**
** 새로운 구성 옵션은 SQLite는 이후 릴리스에서 추가 할 수 있다.
** 기존 구성 옵션 을 중지하는 경우가 있습니다. 응용 프로그램
** 확인 하기 위해 [ sqlite3_config ( ) 의 리턴 코드 를 확인 해야 합니다
** 호출 했습니다. [ sqlite3_config 는 ( ) 인터페이스 를 반환합니다
** 제로가 아닌 [ 오류 코드 ] 만약 중단되거나 지원 되지 않는 옵션
** 이 호출됩니다.
**
** <DL>
** [ SQLITE_CONFIG_SINGLETHREAD ] <DT> SQLITE_CONFIG_SINGLETHREAD < / DT >
** 이 옵션 의 인수없이 이 없습니다 <DD> . ^ 이 옵션이 설정 됩니다
** 스레드 모드 싱글 스레드 에 . 즉, 그것은 비활성화
** 모든 뮤텍스 에서 그냥 사용할 수 있는 모드로 SQLite 를 넣어
** 단일 스레드 에서 . ^ 만약 SQLite 는 사용하여 컴파일 된
** [ SQLITE_THREADSAFE | SQLITE_THREADSAFE = 0 ] 컴파일시의 옵션 에서 다음
** 그것은 기본 스레드 모드를 변경할 수 없습니다
** 단일 스레드 값 등 [ sqlite3_config 는 ( ) 로 돌아갑니다
** [ SQLITE_ERROR ] SQLITE_CONFIG_SINGLETHREAD 로 불려 갔을 경우
** 옵션 < / DD >
**
** [ SQLITE_CONFIG_MULTITHREAD ] <DT> SQLITE_CONFIG_MULTITHREAD < / DT >
** 이 옵션 의 인수없이 이 없습니다 <DD> . ^ 이 옵션이 설정 됩니다
** 멀티 스레드 의 모드 스레딩 ] . 즉, 그것은 비활성화
** 데이터베이스 연결 및 준비된 문 개체 에서 뮤텍스 .
** 응용 프로그램 에 대한 액세스를 직렬화 할 책임이있다
** 데이터베이스 연결 및 준비된 문 ] . 그러나 다른 뮤텍스
SQLite 는 멀티 스레드 에서 사용해도 안전 하다는 것을 ** 이 활성화 되어 있습니다
** 환경이라면 , 두 개의 스레드 가 동일한 사용 하지 않도록
** 동시에 데이터베이스 연결 . ^ 만약 SQLite 는 사용하여 컴파일 된
** [ SQLITE_THREADSAFE | SQLITE_THREADSAFE = 0 ] 컴파일시의 옵션 에서 다음
** 그것은 멀티 스레드 스레드 모드를 설정 하는 것은 불가능 하다고
로 불려 갔을 경우 ** [ sqlite3_config ( ) ] [ SQLITE_ERROR ] 돌아갑니다
** SQLITE_CONFIG_MULTITHREAD 설정 옵션 < / DD >
**
** [ SQLITE_CONFIG_SERIALIZED ] <DT> SQLITE_CONFIG_SERIALIZED < / DT >
** 이 옵션 의 인수없이 이 없습니다 <DD> . ^ 이 옵션이 설정 됩니다
** 직렬화 에 모드 스레딩 ] . 즉, 이 옵션 이 활성화
** 재귀 를 포함한 모든 mutex
** 데이터베이스 연결 및 준비된 문 ] 개체에 대한 상호 배타적 잠금 .
SQLite 것이 컴파일 된 때 ** 이 모드는 ( 기본적으로 이것은
** [ SQLITE_THREADSAFE = 1 ] ) SQLite 라이브러리 자체는 액세스 를 serialize합니다
** 데이터베이스 연결 및 미리 컴파일 된 SQL 문 ] 이되도록
** 응용 프로그램은 동일한 데이터베이스 연결을 사용하여 자유로운가? ,
** 동시에 다른 스레드에서 동일한 [ 준비된 문 ] .
** ^ 만약 SQLite 는 사용하여 컴파일 된
** [ SQLITE_THREADSAFE | SQLITE_THREADSAFE = 0 ] 컴파일시의 옵션 에서 다음
** 그것은 직렬화 된 스레드 모드를 설정 할 수 없으며,
로 불려 갔을 경우 ** [ sqlite3_config ( ) ] [ SQLITE_ERROR ] 돌아갑니다
** SQLITE_CONFIG_SERIALIZED 설정 옵션 < / DD >
**
** [ SQLITE_CONFIG_MALLOC ] <DT> SQLITE_CONFIG_MALLOC < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_mem_methods ] 구조체 의 인스턴스 . 인수를 지정합니다
** 다른 낮은 수준의 메모리 할당 루틴 대신 에 사용 하는
** 메모리 할당 루틴은 SQLite 에 포함되어 있다. ) ^ ^ SQLite 는 것
** [ sqlite3_mem_methods ] 구조체 의 내용에 대한 자신의 개인 사본
** [ sqlite3_config ( ) 호출이 돌아 오기 전에 . < / DD >
**
** [ SQLITE_CONFIG_GETMALLOC ] <DT> SQLITE_CONFIG_GETMALLOC < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_mem_methods ] 구조체 의 인스턴스 . [ sqlite3_mem_methods ]
** 구조체 는 현재 정의 된 메모리 할당 루틴 에 만족 하고있다. ) ^
** 이 옵션은 기본 메모리 할당 을 오버로드 하는 데 사용할 수
메모리 할당 오류 또는 시뮬레이션 래퍼 ** 루틴
예를 들어 ** 트랙 의 메모리 사용량 . < / DD >
**
** [ SQLITE_CONFIG_MEMSTATUS ] <DT> SQLITE_CONFIG_MEMSTATUS < / DT >
** <DD> ^ 이 옵션은 해석 int 형식의 단일 인수를 취합니다
메모리 할당 의 수집 을 활성화하거나 비활성화 합니다. ** 부르,
** 통계 . ^ ( 메모리 할당 통계 를 사용할 경우 에는
** 다음 SQLite 인터페이스는 비 작동 된다.
** <UL>
** <LI> [ sqlite3_memory_used ( )
** <LI> [ sqlite3_memory_highwater ( )
** <LI> [ sqlite3_soft_heap_limit64 ( )
** <LI> [ sqlite3_status ( )
** < / UL > ) ^
SQLite 않는 한 ** ^ 메모리 할당 통계는 기본적으로 활성화 되어 있습니다
** [ SQLITE_DEFAULT_MEMSTATUS ] = 0 에서 컴파일 된 . 이 경우 메모리
** 할당 통계는 기본적으로 비활성화되어 있다.
** < / DD >
**
** [ SQLITE_CONFIG_SCRATCH ] <DT> SQLITE_CONFIG_SCRATCH < / DT >
** <DD> ^ 이 옵션은 SQLite 를 사용할 수 정적 메모리 버퍼를 지정하는
** 스크래치 메모리 . 포인터 는 8 바이트로 3 인수가 있습니다.
스크래치 할당 이 바탕이되는 ** 정렬 메모리 버퍼
** 그려진 각 스크래치 할당 ( SZ ) 의 크기,
** 스크래치 할당 의 최대 수 ( N ) . 확인
** 인수가 16 의 배수 여야 합니다.
** 첫 번째 인수는 8 바이트 정렬 버퍼 에 대한 포인터 이어야 합니다
** 적어도 확인 * 메모리 N 바이트 .
** ^ SQLite 는 스레드 마다 몇 개 이상의 스크래치 버퍼를 사용 하지 않습니다. 이렇게
** N은 스레드 의 배 예상되는 최대 수로 설정 해야 합니다.
** ^ SQLite 는 6 이상 이다 스크래치 버퍼를 필요로 하지 않습니다
** 시간 데이터베이스 페이지 크기 . ^ 만약 SQLite 는 추가 필요를 필요로한다
이 설정 옵션으로 제공 되는 이상 ** 스크래치 메모리 는
** [ sqlite3_malloc ( ) 메모리 가 필요한 얻기 위해 사용 된다. < / 닫기 >
**
** [ SQLITE_CONFIG_PAGECACHE ] <DT> SQLITE_CONFIG_PAGECACHE < / DT >
** <DD> ^ 이 옵션은 SQLite 를 사용할 수 정적 메모리 버퍼를 지정하는
** 기본 페이지 캐시 구현 을 사용하여 데이터베이스 페이지 캐시 .
** 이 구성은 사용 해서는 않으면 응용 프로그램 정의 페이지
** 캐쉬는 SQLITE_CONFIG_PCACHE2 옵션을 사용하여 로드 됩니다.
** 이 옵션의 세 가지 인수가 있습니다. 정렬 8 바이트 포인터
메모리 ** 각 페이지 버퍼 ( 확인 ) 크기, 페이지 수 ( N ) .
** 확인 인수는 최대 의 데이터베이스 페이지 크기 가 아니면 안됩니다
** ( 512 과 32768 사이 에 2 의 거듭 제곱 ) 과 각각 에 조금 더
** 페이지 헤더입니다. ^ 페이지 헤더 의 크기가 20 ~ 40 바이트 에 의존 하고있다
** 호스트 아키텍처 . ^ 이것은 떨어져 불필요한 메모리 에서 무해하다
** 확인 좀 너무처럼 합니다. 첫 번째
** 인수는 적어도 확인 메모리 * n 바이트 의 할당 을 가리켜 야 합니다.
** ^ SQLite 만족 하는 첫 번째 인수 에 의해 제공되는 메모리 가 사용됩니다 그
** 메모리 는 캐시 에 추가 됩니다 첫 번째 N 페이지를 위해 필요하다. ^ 추가 경우
** 페이지 캐시 메모리는 이 옵션으로 제공 되는 것 이상 필요 다음,
** SQLite 는 추가 저장 공간 을 위해 [ sqlite3_malloc ( ) ] 로 이동 합니다.
** 첫번째 인수 의 포인터 해야합니다
** 8 바이트 또는 SQLite는 그런 행동 에 정렬 시킬 수
** 부정이 됩니다. < / DD >
**
** [ SQLITE_CONFIG_HEAP ] <DT> SQLITE_CONFIG_HEAP < / DT >
** <DD> ^ 이 옵션은 SQLite 에서 사용하는 정적 메모리 버퍼를 지정합니다.
** 제공하는 것을 넘어, 그 동적 메모리 할당 요구 모두를위한
** [ SQLITE_CONFIG_SCRATCH ] 이면서 [ SQLITE_CONFIG_PAGECACHE ] 를 위해.
** 3 인수가 있습니다. 메모리 의 8 바이트 정렬 포인터는
** 메모리 버퍼 의 바이트 수 및 최소 할당 크기 .
첫 번째 포인터 ( 메모리 포인터 ) 가 NULL의 경우 ** ^ 그리고 SQLite 는 돌아갑니다
** 를 기본 메모리 할당 ( 시스템 의 malloc ( ) 의 구현 ) 를 사용 하기로 결정,
** [ SQLITE_CONFIG_MALLOC ] 중 하나 전에 호출 을 취소합니다. ^ 만약
** 메모리 포인터가 NULL이 아니고 , 어느 쪽이든 [ SQLITE_ENABLE_MEMSYS3 ] 또는
** [ SQLITE_ENABLE_MEMSYS5 ] 가 정의 된 경우 대체 메모리
** 할당 은 SQLites 메모리 할당 요구를 모두 처리하기 위해 최선을 다하고 있습니다 .
** 첫 번째 포인터 ( 메모리 포인터 ) 가 8 바이트로 정렬 되어야 한다
** 경계 또는 SQLite는 다음 의 동작은 부정 이됩니다.
** 최소 할당 크기는 2 ** 12 을 초과 할 수 없다 . 합리적인 값
** 최소 할당 크기로 ** 5 2 2 ** 8 까지입니다. < / DD >
**
** [ SQLITE_CONFIG_MUTEX ] <DT> SQLITE_CONFIG_MUTEX < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_mutex_methods ] 구조체 의 인스턴스 . 인수를 지정합니다
** 다른 낮은 수준의 뮤텍스 루틴이 대신 사용되는
** 뮤텍스 루틴 은 SQLite 에 포함되어 있다. ) ^ ^ SQLite 는의 복사본을 만듭니다
** 의 호출 전에 [ sqlite3_mutex_methods ] 구조체 의 내용
** [ sqlite3_config ( ) ] 로 돌아갑니다. ^ 만약 SQLite 는 사용하여 컴파일 된
** [ SQLITE_THREADSAFE | SQLITE_THREADSAFE = 0 ] 컴파일시의 옵션 에서 다음
** 전체 mutex 화 서브 시스템은 빌드 에서 제외하고, 따라서 호출 하는
** [ sqlite3_config ( ) ] SQLITE_CONFIG_MUTEX 설정 옵션 이됩니다
** [ SQLITE_ERROR 을 반환합니다. < / DD >
**
** [ SQLITE_CONFIG_GETMUTEX ] <DT> SQLITE_CONFIG_GETMUTEX < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_mutex_methods ] 구조체 의 인스턴스 . 더
** [ sqlite3_mutex_methods ]
** 구조체 는 현재 정의 된 뮤텍스 루틴 충족 . ) ^
** 이 옵션은 기본 뮤텍스 할당을 오버로드 하는 데 사용할 수
** 사용 래퍼 루틴은 성능 을위한 뮤텍스 의 사용을 추적 하는
** 프로파일 링 및 테스트 , 예를 들면. ^ 만약 SQLite 는 사용하여 컴파일 된
** [ SQLITE_THREADSAFE | SQLITE_THREADSAFE = 0 ] 컴파일시의 옵션 에서 다음
** 전체 mutex 화 서브 시스템은 빌드 에서 제외하고, 따라서 호출 하는
** [ sqlite3_config ( ) ] SQLITE_CONFIG_GETMUTEX 설정 옵션 이됩니다
** [ SQLITE_ERROR 을 반환합니다. < / DD >
**
** [ SQLITE_CONFIG_LOOKASIDE ] <DT> SQLITE_CONFIG_LOOKASIDE < / DT >
** <DD> ^ ( 이 옵션은 기본적 를 결정 하는 2 개의 인수를 취합니다
** 각각 룩 어 사이드 메모리 할당 메모리 할당
** 데이터베이스 연결 . 첫 번째 인수는
** 각 TLB가 슬롯 의 크기는 두 번째 수 있습니다
** 슬롯 은 각 데이터베이스 연결 에 할당 하고있다. ) ^ ^ ( 이 옵션이 설정 됩니다
** <I> 기본 < / i > 모양 -aside 사이즈. [ SQLITE_DBCONFIG_LOOKASIDE ]
** [ sqlite3_db_config ( ) 동사 조회 아 사이드 를 변경 하는 데 사용할 수있는
** 개별 연결 설정. ) ^ < / DD >
**
** [ SQLITE_CONFIG_PCACHE2 ] <DT> SQLITE_CONFIG_PCACHE2 < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_pcache_methods2 개체 . 이 개체는 인터페이스를 지정
** 사용자 지정 페이지 캐시 구현 . ) ^ ^ SQLite 는의 복사본을 만듭니다
** 개체 와 페이지 캐시 메모리 할당 을 위해 그것을 사용 하고 있습니다 . < / DD >
**
** [ SQLITE_CONFIG_GETPCACHE2 ] <DT> SQLITE_CONFIG_GETPCACHE2 < / DT >
** <DD> ^ ( 이 옵션은 포인터 인 단일 인수를 취
** [ sqlite3_pcache_methods2 개체 . 현재 SQLite 복사
** 해당 개체 에 페이지 캐시 를 구현하고 있습니다. ) ^ < / DD >
**
** [ SQLITE_CONFIG_LOG ] <DT> SQLITE_CONFIG_LOG < / DT >
** SQLITE_CONFIG_LOG 옵션은 SQLite 를 설정 하는 데 사용 됩니다 <DD>
** 국제 오류 로그 .
** ( ^ SQLITE_CONFIG_LOG 옵션은 2 개의 인수를 취합니다. 포인터를
** 무효 의 호출 부호 ( * ) (무효 * , int 형 상수 char * ) 가있는 함수
** 와 void 포인터 . 함수 포인터가 NULL이 아닌 경우 ^ 그렇습니다
** 각 로깅 이벤트를 처리 하기 위해 [ sqlite3_log ( ) 에 의해 호출 . ^ 만약
** 함수 포인터는 [ sqlite3_log ( ) 인터페이스는 노 오퍼레이션 이되지 않습니다 NULL입니다 .
** ^ SQLITE_CONFIG_LOG 의 두 번째 인수 인 void 포인터 이다
** 응용 프로그램 정의 로거 의 첫 번째 매개 변수로 전달
** 함수가 호출 될 때마다 기능 . ^ 두번째 매개 변수
** 로거 기능은 해당 첫 번째 매개 변수 의 복사
** [ sqlite3_log ( ) 를 호출하여 결과 코드 또는 다는 것을 의도 하고있다
** 결과 코드를 확장 . ^ 로거 에 전달되는 세 번째 매개 변수 가 있는
** [ sqlite3_snprintf ( ) 를 통해 포맷 한 후 메시지 를 기록 합니다.
** SQLite 로깅 인터페이스는 재진입 하지 않습니다. 로거 기능
** 어플리케이션이 제공 어떤 SQLite 인터페이스를 호출 하지 말라 .
** 멀티 스레드 응용 프로그램은 응용 프로그램 정의 로거
** 이 함수는 스레드로부터 안전 해야 합니다. < / DD >
**
** [ SQLITE_CONFIG_URI ] <DT> SQLITE_CONFIG_URI
** <DD> ^ ( 이 옵션은 int 형식의 단일 인수를 취합니다. 경우 0이 아닌 경우
** URI 처리 를 전역 적으로 활성화 되어 있다. 매개 변수 가 제로의 경우 의 URI 처리 하는 경우
** 세계적으로 비활성화 됩니다. ) ^ ^ URI 처리 가 전역으로 설정 되어 있는 경우, 모든 파일 이름
** 에 전달 [에서 sqlite3_open ( ) , sqlite3_open_v2 ( ) , sqlite3_open16 ( ) 또는
** 의 일부로 지정된 첨부 명령 은 URI 의 해석 되는 에 관계없이
** [ SQLITE_OPEN_URI 플래그가 설정되어 있는지 의 때 데이터베이스
** 연결이 열립니다. ^ 그것이 세계적으로 비활성화 되어있는 경우 파일 이름은
SQLITE_OPEN_URI 플래그가 설정되어 있는 경우 ** URI 로만 해석 할 때
** 데이터베이스 연결이 열립니다. ^ ( 기본적으로 URI 처리 는 글로벌
** 사용할 수 있습니다. 기본값은 사용하여 컴파일 함으로써 변경 될 수 있습니다
** [ SQLITE_USE_URI ] 기호가 정의 되어 있다. ) ^
**
** [ SQLITE_CONFIG_COVERING_INDEX_SCAN ] <DT> SQLITE_CONFIG_COVERING_INDEX_SCAN
** <DD> ^ 이 옵션은 해석 되는 단일 정수 인수를
** 인덱스를 커버 의 사용 을 활성화하거나 비활성화 하는 부울
** 쿼리 최적화 프로그램 에서 전체 테이블 스캔 . ^ 기본 설정은 결정된다
** [ SQLITE_ALLOW_COVERING_INDEX_SCAN ] 컴파일 시 의 옵션 또는 "정상" 이다
** 그 컴파일러 옵션이 생략 되는 경우 .
** 풀 테이블 스캔 을위한 지표 를 커버 의 사용 을 해제하는 기능
일부 잘못 코딩 된 기존 응용 프로그램 은 오동작하는 경우가 있기 때문에, ** 입니다
** 최적화 가 활성화되어 있을 때 . 하는 기능을 제공
** 비활성화 최적화는 나이 의 버그가 응용 프로그램 코드 를 실행하는 것을 허용한다
** 하지만 SQLite 는 새로운 버전으로 변경 하지 않고.
**
** [ SQLITE_CONFIG_PCACHE ]] [[ SQLITE_CONFIG_GETPCACHE ]
** <DT> 의 SQLITE_CONFIG_PCACHE 과 SQLITE_CONFIG_GETPCACHE
** <DD> 이 옵션은 폐지되고 새로운 코드 에서는 사용 하지 마십시오 .
**이 는 역 호환성 을 위해 남겨 아니라 지금은 조합 되어 있지 않습니다.
** < / DD >
**
** [ SQLITE_CONFIG_SQLLOG ]
** <DT> SQLITE_CONFIG_SQLLOG
SQLite 것이 컴파일 된 경우 ** <DD> 이 옵션은 볼 수 있습니다
** [ SQLITE_ENABLE_SQLLOG ] 전 처리기 매크로가 정의 되어 있다. 첫 번째 인수는 해야
, void ** 형 ( * ) (무효 * sqlite3 의 * , const char * 는 int ) 함수 에 대한 포인터 이다.
** 두 형 (무효 * ) 이어야 합니다. 콜백 라이브러리가 호출됩니다
** 3 개의 서로 다른 상황에서 로 전달 된 값으로 식별
** 네 번째 매개 변수 . 네 번째 매개 변수 는 0, 데이터베이스 연결 의 경우
두 번째 인수가 다만 열린 같이 ** 통과되었다. 세번째 인수
** 주 데이터베이스 파일 의 이름을 포함한 버퍼 를 가리킨다. 만약
** 4 번째 매개 변수는 SQL 문 1 임을 셋째 인수
** 포인트 는 직전에 실행되고 있습니다. 또는 네 번째 매개 변수는 다음 두 경우
** 번째 매개 변수로 전달 된 연결이 닫혀있다. 더
** 번째 매개 변수는 이 경우 NULL을 전달합니다. 이것을 사용하는 방법
** 설정 옵션은 " test_sqllog.c " 소스 파일에서 볼 수 있습니다
** 정규 SQLite 의 소스 트리 . < / DD >
**
** [ SQLITE_CONFIG_MMAP_SIZE ]
** <DT> SQLITE_CONFIG_MMAP_SIZE
** <DD> ^ SQLITE_CONFIG_MMAP_SIZE 는 2 개의 64 비트 정수 ( sqlite3_int64 ) 의 값을 갖는다
** 기본 mmap 크기 제한 ( 기본 설정되어 있는지
** [ 프라 그마 mmap_size ] ) 및 최대 허용 mmap 크기 제한 .
** ^ 기본 설정은 사용하여 각 데이터베이스 연결 덮어 쓸 수 있습니다
** [ PRAGMA mmap_size 명령 또는 사용하여 어느
** [ SQLITE_FCNTL_MMAP_SIZE ] 파일 제어 . ^ ( 최대 허용 의 mmap 크기
** 런타임에 변경할 수 없습니다. NOR 최대 값은 mmap 크기 동물 수
** 로 구성된 컴파일 시 최대 mmap 크기를 초과
** [ SQLITE_MAX_MMAP_SIZE ] 컴파일 시 옵션 . ) ^
이 옵션 중 하나 의 인수가 부의 경우 ** ^ 그 인수가
** 그 컴파일 기본 설정 값으로 변경 되었습니다.
**
** [ SQLITE_CONFIG_WIN32_HEAPSIZE ]
** <DT> SQLITE_CONFIG_WIN32_HEAPSIZE
** <DD> ^ 이 옵션은 제공되는 SQLite 는 Windows 용으로 컴파일 된 경우
** [ SQLITE_WIN32_MALLOC ] 전 처리기 매크로가 정의 되어 .
** SQLITE_CONFIG_WIN32_HEAPSIZE 32 비트 부호없는 정수 값을 취
** 그것이 생성 된 힙 의 최대 크기를 지정 합니다.
** < / DL >
* /
#define SQLITE_CONFIG_SINGLETHREAD  1  /* nil */
#define SQLITE_CONFIG_MULTITHREAD   2  /* nil */
#define SQLITE_CONFIG_SERIALIZED    3  /* nil */
#define SQLITE_CONFIG_MALLOC        4  /* sqlite3_mem_methods* */
#define SQLITE_CONFIG_GETMALLOC     5  /* sqlite3_mem_methods* */
#define SQLITE_CONFIG_SCRATCH       6  /* void*, int sz, int N */
#define SQLITE_CONFIG_PAGECACHE     7  /* void*, int sz, int N */
#define SQLITE_CONFIG_HEAP          8  /* void*, int nByte, int min */
#define SQLITE_CONFIG_MEMSTATUS     9  /* boolean */
#define SQLITE_CONFIG_MUTEX        10  /* sqlite3_mutex_methods* */
#define SQLITE_CONFIG_GETMUTEX     11  /* sqlite3_mutex_methods* */
/* previously SQLITE_CONFIG_CHUNKALLOC 12 which is now unused. */ 
#define SQLITE_CONFIG_LOOKASIDE    13  /* int int */
#define SQLITE_CONFIG_PCACHE       14  /* no-op */
#define SQLITE_CONFIG_GETPCACHE    15  /* no-op */
#define SQLITE_CONFIG_LOG          16  /* xFunc, void* */
#define SQLITE_CONFIG_URI          17  /* int */
#define SQLITE_CONFIG_PCACHE2      18  /* sqlite3_pcache_methods2* */
#define SQLITE_CONFIG_GETPCACHE2   19  /* sqlite3_pcache_methods2* */
#define SQLITE_CONFIG_COVERING_INDEX_SCAN 20  /* int */
#define SQLITE_CONFIG_SQLLOG       21  /* xSqllog, void* */
#define SQLITE_CONFIG_MMAP_SIZE    22  /* sqlite3_int64, sqlite3_int64 */
#define SQLITE_CONFIG_WIN32_HEAPSIZE      23  /* int nByte */
/ *
** CAPI3REF : 데이터베이스 연결 구성 옵션
**
**이 상수는 사용할 수있는 정수 의 설정 옵션 임을
** [ sqlite3_db_config ( ) 인터페이스 의 두 번째 인수로 전달할 수 있습니다.
**
** 새로운 구성 옵션은 SQLite는 이후 릴리스에서 추가 할 수 있다.
** 기존 구성 옵션 을 중지하는 경우가 있습니다. 응용 프로그램
** 확인 하기 위해 [ sqlite3_db_config ( ) 의 리턴 코드 를 확인 해야 합니다
** 호출 했습니다. ^ [ sqlite3_db_config 는 ( ) 인터페이스 를 반환합니다
** 제로가 아닌 [ 오류 코드 ] 만약 중단되거나 지원 되지 않는 옵션
** 이 호출됩니다.
**
** <DL>
** <DT> SQLITE_DBCONFIG_LOOKASIDE < / DT >
** <DD> ^ 이 옵션을 결정 하는 3 개의 추가 인수를 취합니다.
데이터베이스 연결 에 대한 ** [ 룩 아 사이드 메모리 할당 의 구성 .
** ^ 첫 번째 인수 ( 세 번째 매개 변수 [ sqlite3_db_config 은 ( ) 이다
** 메모리 버퍼의 포인터 모양 -aside 메모리 에 사용 한다.
** ^ SQLITE_DBCONFIG_LOOKASIDE 동사 의 후 첫 인수
** SQLite 를 할당합니다 그 경우 NULL을 지정할 수
** 룻쿠아 [ sqlite3_malloc 를 ( ) 를 사용하여 자신을 버퍼링 한다. ^ 두 번째 인수는 있다
각 TLB가 슬롯 ** 사이즈. ^ 세번째 인수 는 숫자 이다
** 슬롯 . 첫 번째 인수 의 버퍼 크기 가 더 커야 합니다
** 또는 두 번째 및 세 번째 인수 의 곱 과 같다. 버퍼
** 8 바이트 경계 에 정렬 되어야 한다. ^ 두번째 인수 하는 경우
** SQLITE_DBCONFIG_LOOKASIDE 는 8의 배수 가 아닌, 그것은 내부 에서
** 8 다음 작은 배수로 내림 . ^ ( 룩 아 사이드 메모리
** 데이터베이스 연결 을위한 설정을 변경할 수 때
** 연결이 현재 룩 어 사이드 메모리 를 사용 하지 않는 , 즉
" 현재 값 " 안에 반환된다. ** 때
** [ sqlite3_db_status ( D [ SQLITE_CONFIG_LOOKASIDE , ... ) 은 0이다.
** 룩 어 사이드 메모리 구성을 변경 하려고 하면 룻쿠아
** 메모리 는 사용 중인 구성 변경하지 않고 반환 남기고있다
** [ SQLITE_BUSY ] ) ^ < / DD >
**
** <DT> SQLITE_DBCONFIG_ENABLE_FKEY < / DT >
** <DD> ^ 이 옵션은 시행 을 활성화하거나 비활성화 하는 데 사용 되는
** 외래 키 제약 조건 . 2 추가 인수가 있어야합니다.
** 첫 번째 인수는 FK 의 강제 를 해제 하려면 0 인 정수입니다
** 양 FK 집행을 남기기 위해서, FK 의 집행 또는 음수 를 사용하려면
** 다르지 않다. 두 번째 매개 변수는 정수에 대한 포인터 로 그 안에
** 는 0 또는 1 이 FK 의 집행이 꺼져 있거나 켜져 있는지 여부를 나타 내기 위해 써진
** 이 호출 다음 . 두 번째 매개 변수는 이 NULL 포인터 이다
** 그 때 FK 강제 설정은 다시 보고 되지 않습니다. < / DD >
**
** <DT> SQLITE_DBCONFIG_ENABLE_TRIGGER < / DT >
** <DD> ^ 이 옵션은 | 트리거 트리거 만들기 를 활성화하거나 비활성화 하는 데 사용 됩니다.
** 2 추가 인수가 있어야합니다.
** 첫 번째 인수는 트리거를 비활성화 하려면 0 인 정수입니다
** 양 변하지 않는 설정을 남기기 위해 트리거 또는 네거티브 필름을 사용 합니다.
** 두번째 매개 변수는 정수에 대한 포인터 로 그 안에
** 는 0 또는 1 의 트리거 가 잘못되었거나 유효한지 여부 를 나타 내기 위해 써진
** 이 호출 다음 . 두 번째 매개 변수는 이 NULL 포인터 이다
** 이 경우 트리거 설정은 다시 보고 되지 않습니다. < / DD >
**
** < / DL >
* /
#define SQLITE_DBCONFIG_LOOKASIDE       1001  /* void* int int */
#define SQLITE_DBCONFIG_ENABLE_FKEY     1002  /* int int* */
#define SQLITE_DBCONFIG_ENABLE_TRIGGER  1003  /* int int* */


/ * 
** CAPI3REF : 사용하거나 확장 결과 코드를 해제하려면 
** 
** ^ sqlite3_extended_result_codes () 루틴은 활성화 또는 비활성화합니다 
SQLite의 ** 확장 결과 코드 기능. ^ 확장 결과 
** 코드는 역사적인 호환성을 위해 기본적으로 비활성화되어 있습니다. 
* /
SQLITE_API int sqlite3_extended_result_codes(sqlite3*, int onoff);

/ *
** CAPI3REF : 라스트 삽입 ROWID 의
**
** ^ ( 없음 ROWID 테이블을 제외한 ) 대부분의 SQLite 테이블 의 각 항목
** 독특한 64 비트 부호 붙었습니다
라는 ** 정수 키 [ ROWID | " ROWID " ] . ^ ROWID 는 항상 사용할 수 있습니다
** 수만 있다면 , ROWID , OID 또는 _ROWID_ 라는 선언 되지 않은 열로
** 이름 도 명시 적으로 선언 된 컬럼에서는 사용 되지 않습니다 . ^ 만약
** 표는 유형 정수 PRIMARY KEY ] 열이 , 열
** ROWID 를위한 다른 별명입니다.
**
** ^ sqlite3_last_insert_rowid ( D ) 인터페이스는 , ROWID ] 를 반환
** ROWID 테이블 에 성공한 최신 의 삽입 또는 가상 테이블
** 데이터베이스 연결 D 에
** ^ [ WITHOUT ROWID ] 테이블에 삽입 은 기록 되지 않습니다 .
** ^ 전혀 성공 [ INSERT ] 는 ROWID 테이블 에 예정 없는 경우
** 지금까지 의 데이터베이스 연결 D 에 발생한
** 그리고, ( D ) sqlite3_last_insert_rowid 0 을 반환합니다.
**
** ^ ( [ INSERT ] 는 트리거 또는 가상 테이블 에서 발생하면
** 이 방법 이 루틴 은 [ ROWID ] 삽입 된 것을 돌려줍니다
** 트리거 또는 가상 테이블 방식 만큼 긴 줄 이 실행되고 있습니다.
트리거 또는 가상 테이블 법이 완료되면 ** 하지만 값을 반환
** 이 루틴 그것이 전에 있던 무슨 에 반환 트리거 또는 가상
** 테이블 방식 이 시작되었다. ) ^
**
** ^ 인한 제약 조건 위반으로 인해 실패한 제거 [ INSERT ] 이 없습니다
** 성공 삽입 따라서 반환 된 값을 변경할 수는 없습니다.
** 일과. ^ 이렇게 삽입 하거나 실패한 경우, INSERT 또는 IGNORE INSERT 또는 ROLLBACK ,
** 및 INSERT 또는 이것의 반환 값 을 변경 하지 ABORT
** 루틴 그들의 삽입 에 실패 했을 때. ^ ( 때 INSERT 또는 REPLACE
** 제약 조건 위반이 발생한 그것이 실패 하지 않습니다. 더
** INSERT가 발생 된 행을 삭제 한 후에 완료 될 때까지 계속
** 제약 문제는 그런 식으로 항상 변화를 삽입 하거나 REPLACE
** 이 인터페이스 의 반환 ) . ^
**
** ^ 이 루틴 의 목적을 위해 , INSERT ] 는 생각할 수 있다
그 다음 으로 롤백 되어도 ** 성공한다.
**
** 이 함수는 통해 SQL 문장 에 액세스 할 수
** [ last_insert_rowid ( ) SQL 함수 .
**
** 다른 스레드가 동일한 위에 새로운 삽입을 실행 한 경우
** 데이터베이스 연결 중에 [ sqlite3_last_insert_rowid ( )
** 이 함수는 실행되고 있기 때문에, 마지막에 삽입하는 [ ROWID 를 변경하고
** 지금까지 반환 된 값 [ sqlite3_last_insert_rowid 은 ( ) 이다
** 예측할 신구 어딘가에 동일 하지 않을 수 있습니다
** 마지막 [ ROWID ] 삽입합니다.
* /
SQLITE_API sqlite3_int64 sqlite3_last_insert_rowid(sqlite3*);
/ *
** CAPI3REF : 변경된 행 의 수 계산
**
** ^ 이 함수는 변경된 데이터베이스 의 행을 반환
** 또는 마지막으로 완료 한 SQL 문 에서 삽입 또는 삭제
** 데이터베이스 연결 의 첫 번째 매개 변수 로 지정 되었다.
** ^ ( 직접 삽입 에서 지정된 변경 사항 만 새로 고침 ,
** 또는 삭제 문이 계산 됩니다. 에 기인 한 보조 변경
** 트리거 또는 외래 키 액션 ] 은 포함되지 않습니다. ) ^ 사용
** [ sqlite3_total_changes ( ) ] 변경 의 총 수를 검색 하는 기능
** 트리거 및 외래 키 동작 에 기인 한 변경 을 포함한다.
**
** ^ [ INSTEAD OF 트리거 에 의해 시뮬레이션 된 뷰로 변경
** 는 포함되지 않습니다. 유일한 진짜 테이블 의 변경 이 계산 됩니다.
**
** ^ ( " 행 의 변경 "은 단일 테이블 의 하나의 행 으로 변경 합니다
** INSERT, DELETE 또는 UPDATE 문 에 기인한다. 행 수
** 는 바꾸기 제약 해상도 의 부작용으로 변경된
** 롤백 처리 , DROP TABLE 을 ] ABORT 또는 기타 에 의하여,
** 메커니즘은 직접 행 의 변경 을 계산하지 않습니다. ) ^
**
** " 트리거 컨텍스트 는 " 시작 되고 실행 의 범위 입니다
[ | 트리거 트리거를 만들기 ** 스크립트 로 끝납니다.
** 대부분의 SQL 문 은
** 어떤 트리거 외부에서 평가 했다. 이것은 " 최상위 "이다
** 트리거 컨텍스트 . 만약 최상위 에서 트리거가 발생 ,
** 새로운 트리거 컨텍스트는 1 기간 동안 입력 되는
** 트리거 . Subtriggers 는 그 기간 동안 서브 컨텍스트를 만듭니다.
**
** ^ [ sqlite3_exec ( ) 를 호출 하거나 sqlite3_step ( ) 재귀 적으로 수행합니다
** 새로운 트리거 컨텍스트를 생성 하지 않는다.
**
** ^ 이 함수는 직접 행 변경 의 수를 돌려줍니다
** 이전의 INSERT , UPDATE 또는 같은 내 DELETE 문
** 트리거 컨텍스트 .
**
최상위 에서 호출 될 때 ** ^ 이와 같이, 이 함수는 반환합니다
** 이전의 INSERT , UPDATE 또는 DELETE 의 변화 의 수
** 그것도 최상위 발생 했습니다. ^ ( 트리거 본문에서
** sqlite3_changes ( ) 인터페이스는 수를 찾기 위해 호출 할 수 있습니다
마지막으로 완료된 INSERT, UPDATE 또는 DELETE 에서 ** 의 변화
** 같은 트리거 의 본체 의 문 .
** 그러나 반환되는 숫자 는 변경 사항이 포함 되어 있지 않습니다
** 그들이 자신의 컨텍스트를 가지고 있기 때문에 subtriggers 에 기인한다. ) ^
**
** 도 [ sqlite3_total_changes ( ) 인터페이스를 참조하십시오
** [ count_changes 프라 그마 및 변경 내용 ( ) SQL 함수 .
**
** 다른 스레드가 동일한 데이터베이스 연결로 변경 한 경우
** [ sqlite3_changes 는 ( ) 의 값이 반환되고 실행 중
** 예측할 수없는 의미가 없습니다.
* /
SQLITE_API int sqlite3_changes(sqlite3*);

/ *
** CAPI3REF : 변경된 행 의 총 수
**
** ^ 이 함수는 삽입 에 기인 한 행 의 변경 의 수를 반환
** [ 업데이트 또는 데이터베이스 연결 이 열리고 나서 문장 삭제를 .
** ^ ( ) sqlite3_total_changes ( 에 의해 반환되는 숫자는 모든 변경 사항이 포함 되어 있습니다
** 모든 트리거 만들기 | 트리거 컨텍스트 에 의해 만들어진 변경
** 외래 키 액션 . 그러나
** 횟수가 제한 바꾸기를 구현 하는 데 사용 되는 변경 사항이 포함 되어 있지 않습니다 ,
** 롤백 을 수행하거나 처리 하거나 DROP TABLE 의 ] 처리를 중지 합니다. 더
** 카운트는 [ INSTEAD OF 트리거 화재 뷰 의 행을 포함 하지 않습니다 ,
** 그러나 INSTEAD OF 트리거 의 자신의 변화, 그 변경 한 경우
** 계산 됩니다. ) ^
** ^ sqlite3_total_changes ( ) 함수는 가능한 한 빨리 변경 을 계산
** 그들을 만드는 문장은 때 문 핸들 ( 완료
** [ sqlite3_reset ( ) 또는 sqlite3_finalize ( ) ] ) 에 전달됩니다.
**
** 도 [ sqlite3_changes ( ) 인터페이스를 참조하십시오
** [ count_changes 프라 그마 및 total_changes ( ) SQL 함수 .
**
** 다른 스레드가 동일한 데이터베이스 연결로 변경 한 경우
** [ sqlite3_total_changes 는 ( ) 값을 실행 중에
** 반환 은 예측할 수없는 의미가 없습니다.
* /
SQLITE_API int sqlite3_total_changes(sqlite3*);

/ *
** CAPI3REF : 장기 실행 쿼리를 중단
**
** ^ 이 함수는 중단 보류중인 데이터베이스 작업을 일으키는 원인이되고
** 가장 이른 기회 로 돌아갑니다. 이 루틴은 일반적으로
** " 취소 " 를 누르는 등 의 사용자 액션 에 대한 응답으로 호출
사용자가 정지 하는 긴 쿼리 작업 을 원하는 ** 또는 Ctrl - C
** 빨리.
**
** ^ 그것은 에서 또 다른 스레드 에서 이 루틴을 호출해도 안전합니다
** 그것은 현재 의 데이터베이스 작업을 수행 하는 스레드 . 하지만
** 데이터베이스 연결에서 이 루틴을 호출하는 것은 안전 하지 않습니다 수
** 이 닫혔는지 sqlite3_interrupt ( ) 가 복귀하기 전에 닫을 수 있습니다.
**
** ^ SQL 작업 은 매우 가까울 종료되면 때
** sqlite3_interrupt ( ) 가 호출되고 그것은 기회가 있지 않을 가능성 이 있습니다
** 중단되고 완료 를 계속하는 경우 가 있습니다.
**
** ^ 중단 된 SQL 작업은 [ SQLITE_INTERRUPT 가 반환 됩니다.
** ^ 중단 SQL 조작 은 INSERT, UPDATE 또는 DELETE 의 경우
** 그 후 명시 적 트랜잭션 트랜잭션이
** 자동으로 롤백 됩니다.
**
모두가 현재 실행 까지 ** ^ sqlite3_interrupt ( D ) 의 호출 은 유효하다
데이터베이스 연결 의 D 완전히 ** SQL 문 . ^ 무슨 새로운 SQL 문
** sqlite3_interrupt ( ) 호출 후 와 전에 시작 되었는지
** 문을 실행 하면 그들이 했던 것처럼 제로 가 중단 되어 도달 한
** 전 sqlite3_interrupt ( ) 를 호출하여 실행 . ^ 새로운 SQL 문
실행중인 문장 의 카운트가 제로 이다 에 도달 한 후 ** 시작 되었는지
** sqlite3_interrupt ( ) 의 영향을 받지 않는다.
** ^ 무엇 달리기가 없는 경우 에 발생 하는 통화 ( D ) 를 sqlite3_interrupt 하기
** SQL 문은 아무것도하지 않고, SQL 문 에 영향을주지 않습니다
** sqlite3_interrupt ( ) 호출이 반환 한 후에 시작 된다.
**
** 데이터베이스 연결이 닫힌 경우 잠시 [ sqlite3_interrupt ( )
** 는 그런 나쁜 것은 아마 일어납니다 실행되고 있습니다.
* /
SQLITE_API void sqlite3_interrupt(sqlite3*);
/ *
** CAPI3REF : SQL 문이 완료되었는지 여부를 확인
**
**이 루틴은 결정하기 위해 명령 줄 입력 시에 도움 여부
** 현재 입력 된 텍스트는 전체 SQL 또는 을 형성하고있는 것 같다
** 추가 입력은 텍스트 를 전송 하기 전에 필요한 경우
** 구문 분석을위한 SQLite . ^ 이러한 루틴은 리턴 1 의 경우 입력 문자열
** 전체 SQL 문장 처럼 보입니다. ^ 문장이 있다고 판정 된
그것은 토큰 세미콜론으로 끝나면 접두사 가 없습니다. ** 완료된 경우
** CREATE TRIGGER 문 성형 . ^ 내에 포함 된 세미콜론
** 문자열 리터럴 또는 인용 식별자 의 이름 또는 주석이 없습니다
** 독립 한 토큰 ( 그들이 인 토큰 의 일부 이다
** 임베디드 ) , 그래서 문장의 종료 로 간주 되지 않습니다 . ^ 빈
마지막 세미콜론 을 따르는 ** 과 주석을 무시 합니다.
**
글이 불완전한 경우 ** ^ 이러한 루틴은 0 을 반환합니다. ^ 만약
** 메모리 할당 에 실패한 경우 SQLITE_NOMEM 가 반환됩니다.
**
** ^ 이러한 루틴은 이와 같이 SQL 문을 구문 분석 할 수 없습니다.
** 구문 적으로 잘못된 SQL을 검출 하지 않습니다.
**
** ^ ( SQLite 를 사용하여 초기화되지 않은 경우 sqlite3_initialize ( ) 전
** sqlite3_complete16 시작 ( ) 하고 sqlite3_initialize ( )가 불려
** 자동으로 sqlite3_complete16 ( ) . 그 초기화가 실패 했을 경우,
** 다음 sqlite3_complete16 의 반환 값 은 ( ) 제로 이외 합니다
** 관계없이 입력 SQL을 완료했는지 여부 . ) ^
**
** [ sqlite3_complete ( ) 의 입력은 0으로 종료 해야 합니다
** UTF -8 문자열입니다.
**
** [ sqlite3_complete16 ( ) 의 입력은 0으로 종료 해야 합니다
** 네이티브 바이트 순서 UTF- 16 문자열입니다.
* /
SQLITE_API int sqlite3_complete(const char *sql);
SQLITE_API int sqlite3_complete16(const void *sql);

/ *
** CAPI3REF : SQLITE_BUSY 오류 를 처리하는 콜백 등록
**
** ^ 이 루틴은 언제 호출 될 콜백 함수를 설정합니다
** 시도는 데이터베이스 테이블 을 여는 데 이루어질 수 있도록 다른 스레드
** 또는 프로세스가 잠겨 있습니다.
**
** ^ 바쁜 콜백이 NULL 의 경우 SQLITE_BUSY 또는 SQLITE_IOERR_BLOCKED ]
** 잠금 이 발생 하면 즉시 반환 됩니다. ^ 경우 BUSY 콜백
** 콜백은 2 인수를 사용하여 호출 할 수 있고 NULL이 없습니다.
**
** ^ 바쁜 처리기의 첫 번째 인수는 무효 * 포인터 의 복사
** ) ( sqlite3_busy_handler 세 번째 인수 입니다. ^ 두번째 인수
** 바쁜 핸들러 콜백 은 바쁜 처리기가 한 횟수입니다
** 이 잠금 이벤트 를 위해 호출 되었습니다. ^ 만약
** 바쁜 콜백 0 을 반환하지만, 그 추가 시험은 실시 되지 않습니다
** 데이터베이스에 액세스 하고 SQLITE_BUSY 또는 SQLITE_IOERR_BLOCKED 가 반환 됩니다.
** ^ 콜백이 0이 아닌 반환하는 경우 다른 시도
** 는 읽기 사이클 이 반복 위한 데이터베이스를 여는 데 에 열린다.
**
** 바쁜 처리기 의 존재는 그것이 호출 되는 것을 보증하는 것이 아닙니다
** 잠금 경합 이있는 경우 . ^ 만약 SQLite 결정 하는 열 을 호출
** 처리기가 교착 상태 로 이어질 그것이 가서 돌아갑니다 [ SQLITE_BUSY ]
** 또는 SQLITE_IOERR_BLOCKED ] 대신 바쁜 처리기 를 호출한다.
1 프로세스가 읽기 잠금 을 보유하고있는 경우 ** 시나리오를 고려 하는 것이
** 이것은 예약 된 잠금 에 추진 하려고 하고 있다고 되어 있다
** 두 번째 방법 은 그것이 하려고 하는 예약 된 잠금을 보유하고
** 배타적 잠금 추진하고 있습니다. 첫 번째 프로세스 를 계속할 수 없습니다
** 또한 두 번째와 두 번째 방법 은 없습니다 의해 차단 되어 있기 때문에,
** 그것이 처음 으로 차단 되어 있기 때문에 계속 . 만약 두 프로세스
** 바쁜 처리기를 호출하지 모두 어떤 진보를 이룰 것입니다. 따라서
** SQLite 는 기대하고 첫 번째 프로세스 에 대한 [ SQLITE_BUSY ] 반환 이
** 그 읽기 잠금을 해제 하는 첫번째 프로세스를 시작하고 수 있습니다
** 두 번째 프로세스 가 계속됩니다 .
**
** ^ 기본 바쁜 콜백은 NULL 이다.
**
** ^ [ SQLITE_BUSY ] 오류 가 SQLITE_IOERR_BLOCKED 로 변환되어
** SQLite 는 대규모 트랜잭션 의 중간 일 때 어디에 모든
** 변경 은 인 메모리 캐시 에 맞지 않습니다. SQLite 는 의지
** 이미 데이터베이스 파일 에서 예약 잠금을 유지하지만 , 필요
** 그것은 캐시 를 유출 할 수 있도록 EXCLUSIVE 이 잠금을 촉진
동시에 해가없는 데이터베이스 파일 에 ** 페이지
** 독자. ^ 그것이 잠금을 홍보 할 수없는 경우 에는 메모리
** 캐시 는 이렇게 오류 모순 된 상태 가됩니다
** 코드 에 [ SQLITE_BUSY ] 비교적 양성 에서 상승 함
** [ SQLITE_IOERR_BLOCKED ] 더 엄격한. ^ 이 오류 코드 프로모션
** 변경 자동 롤백 을 강제 합니다. 보기
** 만약, href = " / cvstrac / wiki ? p = CorruptionFollowingBusyError " >
이유 에 대한 논의 를위한 ** CorruptionFollowingBusyError < / a> Wiki 페이지
** 이것은 중요합니다.
**
** ^ (단 마다 정의 된 단일 바쁜 처리기 가있을 수도 있습니다
** 데이터베이스 연결 . 새로운 바쁜 처리기를 설정하면 중 하나를 통과
** 이전 핸들러를 설정 하십시오. ) ^ ^ 그러나 호출 [ sqlite3_busy_timeout ( )
** 도 설정 또는 바쁜 처리기를 지 웁니다.
**
** 바쁜 콜백은 변경 조치 를 취해야 하지 않습니다
** 바쁜 처리기를 시작 하여 데이터베이스 연결 . 어떤 그런 활동
** 정의되지 않은 동작 이 발생한다.
**
** 바쁜 처리기는 데이터베이스 연결을 종료 하지 마십시오
** 또는 바쁜 처리기를 호출 [ 준비된 문 ] .
* /
SQLITE_API int sqlite3_busy_handler(sqlite3*, int(*)(void*,int), void*);

/ *
** CAPI3REF : 세트 바쁜 시간
**
** ^ 이 루틴 세트 [ sqlite3_busy_handler | 바쁜 처리기 ] 잠을
** 지정된 시간에 테이블 이 잠겨 있을 때 . ^ 처리기
** 잠 적어도 「 MS 」 의 밀리 초 까지 많은 시간 대기합니다
** 축적 해 왔습니다. ^ 후 적어도 "MS " 잠 밀리 초
** 처리기는 [ sqlite3_step ( ) 을 ] 일으키는 0 반환 하지만 반환됩니다
** [ SQLITE_BUSY 또는 SQLITE_IOERR_BLOCKED ] .
**
** ^ 제로 이하의 인수로 이 루틴을 호출
** 모든 바쁜 처리기를 사용하지 않도록 합니다.
**
** ^ ( 단순히 특정 위한 단일 바쁜 처리기 가있을 수도 있습니다
** 데이터베이스 연결 중 하나 언제든지 . 만약 다른 바쁜 처리기
** 는 호출하기 전에 ( ) ( sqlite3_busy_handler 을 사용하여 ) 정의 되었습니다
** 이 루틴은 다른 바쁜 처리기 는 클리어 됩니다. ) ^
* /
SQLITE_API int sqlite3_busy_timeout(sqlite3*, int ms);

/ *
** CAPI3REF : 쿼리를 실행하기위한 편리 성 루틴
**
** 이것은 호환성을 위해 유지되고 기존 의 인터페이스입니다.
** 이 인터페이스 는 더 이상 사용 되지 않습니다 .
**
** 정의 : <B> 결과 테이블 < / B > 메모리 데이터 구조로 만들어
** [ sqlite3_get_table ( ) 인터페이스. 결과 테이블 은 레코드
** 전체 쿼리는 하나 이상의 쿼리 에서 유래한다.
**
** 표는 개념적으로 행과 열의 수를 가지고 있습니다. 그러나
**이 숫자는 결과 테이블 자체 의 일부가 아닙니다. 이러한
** 번호 가 별도로 얻을 수있다. N 행 의 수로한다
** 와 M 열의 수 이다 .
**
** 결과 테이블 은 제로로 종료 하는 UTF - 8 문자열 에 대한 포인터 의 배열입니다.
** 배열의 ( N +1 ) * M 의 요소 가있다. 첫 번째 M 포인터 포인트
** 열 이름이 포함 된 제로 로 끝나는 문자열 에 .
** 나머지 항목은 모든 지점 의 결과 를 조회한다. NULL 값은 결과
** NULL 포인터 중. 다른 모든 값은 UTF-8로 0으로 종료 합니다
** 에 의해 반환되는 문자열 표현 [ sqlite3_column_text ( ) .
**
** 결과 테이블 은 하나 이상의 메모리 할당 에서 만들지도 모른다.
** 이것은 [ sqlite3_free ( ) 로 직접 결과 테이블을 전달할 안전 하지 않습니다.
** 결과 테이블을 사용하여 할당 을 해제 해야 합니다 [ ( sqlite3_free_table 을 ) ] .
**
** ^ ( 결과 테이블 형식 의 일례로서 쿼리 결과를 가정
다음과 같이 ** 되어 있습니다 :
**
** <BLOCKQUOTE> <PRE>
** 이름 | 나이
** -----------------------
** 앨리스 | 43
** 밥 | 28
** 신디 | 21
** < / PRE > < / BLOCKQUOTE >
**
** 2 열 ( M == 2 ) 와 3 개의 행 ( N 의 == 3 ) 이있다. 이렇게
** 결과 테이블 은 8 항목이 있습니다. 결과 테이블 이 저장 되어 있다고
** 배열 names azResult 중. 그런 azResult 이 콘텐츠 를 보유하고 있다.
**
** <BLOCKQUOTE> <PRE>
** azResult [0] = " 이름 " ;
** azResult [1] = " 나이 " ;
** azResult [2] = " 앨리스 " ;
** azResult [3] = " 43 " ;
** azResult [4] = " 밥 " ;
** azResult [5] = " 28 " ;
** azResult [6] = " 신디 " ;
** azResult [7] = " 21 " ;
** < / PRE > < / BLOCKQUOTE > ) ^
**
** ^ sqlite3_get_table ( ) 함수는 하나 이상의 평가
** 0으로 종료 하는 UTF - 8 에서 SQL 문을 세미콜론으로 구분 된
** 그 두 번째 인수의 문자열 은 결과 테이블 을 반환합니다.
** 포인터 의 세번째 파라미터로 주어졌다.
**
** 응용 프로그램이 sqlite3_get_table 에서 의 결과 ( ) 로 종료 한 후
** 다음과 같은 목적을 위해 ( ) sqlite3_free_table 결과 테이블 포인터를 전달 해야합니다
** malloc 된 메모리 를 해제합니다. 방법 에 대한
** [ sqlite3_malloc ( ) ) 는 ( sqlite3_get_table 이내에 발생 하고 호출
** 이 함수는 직접 [ ) ( sqlite3_free 를 호출하려고 하지 마십시오 . 만
** [ sqlite3_free_table ( ) 을 적절하고 안전하게 메모리를 해제 할 수 있습니다.
**
** sqlite3_get_table ( ) 인터페이스는 래퍼 로 구현 되어 있습니다
** [ sqlite3_exec ( ) . sqlite3_get_table ( ) 루틴은 권한 이 없습니다.
** SQLite는 하나 의 내부 데이터 구조 에 . 그것은 단지 공공 을 사용 하고 있습니다
** 인터페이스는 여기에서 정의 되었다. 그 결과 , 내부 에서 발생한 오류
** 내부 [ sqlite3_exec ( ) 호출 외부 의 래퍼 계층 은 그렇지 않습니다
** [ sqlite3_errcode ( ) 의 후속 호출 에 반영 되거나
** [ sqlite3_errmsg ( ) .
* /
SQLITE_API int sqlite3_get_table(
  sqlite3 *db,          /* An open database */
  const char *zSql,     /* SQL to be evaluated */
  char ***pazResult,    /* Results of the query */
  int *pnRow,           /* Number of result rows written here */
  int *pnColumn,        /* Number of result columns written here */
  char **pzErrmsg       /* Error msg written here */
);
SQLITE_API void sqlite3_free_table(char **result);
/ *
** CAPI3REF : 포맷 된 문자열 인쇄 기능
**
**이 루틴은 함수 " printf ( ) " 가족 의 워크 같이 사이트 입니다
** 표준 C 라이브러리 .
**
** ^ sqlite3_mprintf ( ) 와 sqlite3_vmprintf ( ) 루틴을 쓴 후
** [ sqlite3_malloc ( ) 에서 가져온 메모리 에 결과 .
**이 2 루틴 에서 반환하는 문자열 이 있어야
** 에 의해 발표 [ sqlite3_free ( ) . ^ 두 루틴 은 반환
** NULL 포인터 [ sqlite3_malloc 은 ( ) 을 충분히 할당 할 수 없는 경우
** 결과 문자열 을 저장하기위한 메모리 .
**
** ^ ( sqlite3_snprintf ( ) 루틴을 " 의 snprintf ( ) " 에서 비슷한
** 표준 C 라이브러리 . 결과 는 쓰여질
** 버퍼 크기 로 주어지는 두번째 매개 변수로 제공
** 첫 번째 매개 변수입니다.尚順
** 처음 두 매개 변수는 ( ) 의 snprintf 에서 반대가됩니다 . ) ^ 입니다
한방울 흘리지 않고 고정 할 수 없습니다. ** 역사적 사고
** 호환성 . ^ ( 에도 주의 sqlite3_snprintf ( )
** 번호 대신 버퍼 에 대한 포인터를 반환
** 문자는 실제로 버퍼 에 기록합니다. ) ^ 우리는 인정
** 쓰여진 문자 의 수가 더 유용한 반환 됩니다
** 값이 , 우리는 sqlite3_snprintf 의 구현 을 변경 ( ) 할 수 없습니다
** 지금 의 호환성을 깨지 않고 .
**
** ^ 않으면 버퍼 크기가 0보다 큰 것처럼 sqlite3_snprintf ( )
** 버퍼는 항상 0으로 종료 임을 보장합니다. ^ 첫번째
** 매개 변수 "N" 은 위한 공간 을 포함하는 버퍼 의 총 크기 이며,
** 제로 터미네이터 . 완전히 할 수 있도록 가장 긴 문자열
** 쓰여진 것은 N - 1 문자 입니다.
**
** ^ sqlite3_vsnprintf ( ) 루틴 은 sqlite3_snprintf 의 가변 인수 버전입니다 ( ) .
**
**이 루틴은 모든 몇 가지 추가 서식 을 구현
** SQL 문을 작성하기 위한 편리한 옵션입니다.
** 일반 printf 모두는 ( ) 의 서식 옵션이 적용 됩니다. 또한 거기
** 는 " % Q ", " % 의 Q" 및 " % 의 Z " 옵션은 다음 과 같습니다.
**
** ^ ( % 의 q 옵션 % s 안에는 대체 하는 것 같이 행동 널 문자로 종료
** 인수 목록 에서 문자열 . 그러나 % q 는 또한 모든 ' \ ' 문자가 배가됩니다 .
** % q 는 문자열 리터럴에 사용 하도록 설계 되어 있습니다 ) ^ 각 ' \ '' 을 배가 하여
** 문자 그것은 그 문자를 탈출 하고 그에 삽입 되는 것을 허용한다
** 문자열입니다.
**
** 예를 들어, 다음과 같이 문자열 변수 ztext 주로 텍스트 가 포함되어 있다고 합니다.
**
** <BLOCKQUOTE> <PRE>
** 시 는 * ztext 의 주요 = "그것은 행복한 일 이다 ! " ;
** < / PRE > < / BLOCKQUOTE >
**
다음과 같이 ** 하나는 SQL 문 이 텍스트를 사용할 수 있습니다.
**
** <BLOCKQUOTE> <PRE>
** CHAR * ZSQL = sqlite3_mprintf ( , ztext 의 기본 " 테이블 의 값 ( ' % 의 Q '). INSERT INTO " ) ;
** sqlite3_exec ( dB, ZSQL , 0, 0, 0 ) ;
** sqlite3_free ( ZSQL ) ;
** < / PRE > < / BLOCKQUOTE >
**
ztext 의 주요 의 ** % 의 Q 포맷 문자열을 사용 하고 있기 때문에 , ' \ ' 문자
** 탈출 하고 다음과 같이 생성 된 SQL 이 되고 있습니다.
**
** <BLOCKQUOTE> <PRE>
** ( ' 이것은 ' 행복한 하루 SA ') TABLE1 에는 값을 삽입
** < / PRE > < / BLOCKQUOTE >
**
** 이것은 맞습니다. 우리는 % s 대신에 % q를 생성 된 SQL을 사용 했다
** 이 보였다 것이다.
**
** <BLOCKQUOTE> <PRE>
** ( "그것은 행복한 날이다 ! ' ) TABLE1 값 에 삽입합니다.
** < / PRE > < / BLOCKQUOTE >
**
** 이 두 번째 예는 SQL 구문 오류입니다. 당신이해야 할 일반적인 규칙으로,
문자열 리터럴 텍스트를 삽입 할 때 ** 항상 대신 % s의 % q를 사용 하고 있습니다 .
**
또한 주위에 작은 따옴표 가 추가됩니다 제외 있어요 ** ^ ( % 의 Q 옵션은 % Q 처럼 작동 합니다
** 총 문자열 밖에. 또한 만약 매개 변수
** 인수 목록 이 NULL 포인터 인 % Q 는없이 ( 텍스트 " NULL " 을 할당
. ** 작은 따옴표 ) ) ^ 따라서 예를 들어, 1 은 말할 수있다 :
**
** <BLOCKQUOTE> <PRE>
** CHAR * ZSQL = sqlite3_mprintf ( , ztext 주를 " 테이블 값 ( % Q ) . INSERT INTO " ) ;
** sqlite3_exec ( dB, ZSQL , 0, 0, 0 ) ;
** sqlite3_free ( ZSQL ) ;
** < / PRE > < / BLOCKQUOTE >
**
** 위의 코드는 ZSQL 에서 올바른 SQL 문을 렌더링합니다
** ztext 의 주요 변수 가 NULL 포인터 에도 변수 .
**
** ^ ( " % Z 의 " 서식 옵션 " % s " 이있다 와 같이 작동합니다
** 또한 문자열이 로드 되고 복사 된 후
** 결과는 [ sqlite3_free ( ) 입력 문자열 에서 호출됩니다. ) ^
* /
SQLITE_API char *sqlite3_mprintf(const char*,...);
SQLITE_API char *sqlite3_vmprintf(const char*, va_list);
SQLITE_API char *sqlite3_snprintf(int,char*,const char*, ...);
SQLITE_API char *sqlite3_vsnprintf(int,char*,const char*, va_list);

/ * 
** CAPI3REF : 메모리 할당 서브 시스템 
** 
** SQLite의 핵심은 자신의 모든에 대해 이러한 세 가지 루틴을 사용하고 있습니다 
** 내부 메모리 할당이 필요하다. 이전 문장의 "핵심" 
** 운영 체제 고유의 VFS 구현이 포함되어 있지 않습니다. 더 
** Windows의 VFS는 일부 작업을 위해 기본 malloc ()과 free ()를 사용하고 있습니다. 
** 
** ^ sqlite3_malloc () 루틴은 블록에 대한 포인터를 반환 
** 메모리의 적어도 N N은 매개 변수이고, 길이는 바이트. 
** ^의 If sqlite3_malloc ()은 충분한 여유를 얻을 수 없다 
** 메모리는 NULL 포인터를 반환합니다. ^ IF 매개 변수 N 
** sqlite3_malloc ()이 0 또는 음수 그 sqlite3_malloc ()가 복귀되는 
** NULL 포인터. 
** 
** ^ 이전에 반환 된 포인터와 sqlite3_free ()를 호출 
** sqlite3_malloc에​​ 따르면 () 또는 sqlite3_realloc ()은되도록 메모리를 해제 
** 그것이 재사용 될 수있다. ^ sqlite3_free () 루틴입니다 
** 무 조작의 경우 NULL 포인터로 호출됩니다. NULL 포인터를 전달 
**) (sqlite3_free에 무해한. 해제 된 후 메모리 
** 읽거나 쓸 수 없다. 하지만 해방 이전에 읽고 
** 메모리는 세그먼트 오류 및 기타 심각한 오류가 발생할 수 있습니다. 
** 메모리 손상, 세그먼트 오류 또는 기타 심각한 오류 
sqlite3_free ()가 NULL이 아닌 포인터로 불려 갔을 경우 ** 발생할 수 있으며, 그 
**) sqlite3_malloc () 또는 sqlite3_realloc (에서 얻을 수 없었다. 
** 
** ^ (sqlite3_realloc () 인터페이스는 크기를 변경하려고합니다 
N은 적어도 N 바이트 수 **하기 전에 메모리 할당 
** 번째 매개 변수입니다. 크기 조정 대상의 메모리 할당이 처음입니다 
** 매개 변수입니다. ) ^ ^ 만약 sqlite3_realloc의 첫 번째 매개 변수 () 
** NULL 포인터가 해당 동작은 호출과 같습니다 
** sqlite3_malloc (N) N은 ()을 sqlite3_realloc 두 번째 매개 변수이다. 
** ^ sqlite3_realloc 두 번째 매개 변수는 ()이 제로인 경우 또는 
** 부정은 그 동작은 호출과 동일합니다. 
** sqlite3_free (P) P는 sqlite3_realloc 첫 번째 매개 변수 ()입니다. 
** ^ sqlite3_realloc ()는 메모리 할당에 대한 포인터를 반환 
** 크기 또는 NULL 적어도 n 바이트의 충분한 메모리를 사용할 수없는 경우. 
** ^ 만약 M이 전에 할당 그만큼 (N, M) 바이트의 크기이다 
** 전에 할당 반환되는 버퍼의 선두에 카피된다 
** sqlite3_realloc ()과 이전 할당을 통해 해제됩니다. 
** ^ sqlite3_realloc ()는 다음 전에 할당 NULL을 반환하는 경우 
** 해제되지 않습니다. 
** 
** ^ 메모리는 sqlite3_malloc ()와 sqlite3_realloc ()에서 반환 된 
** 항상 적어도 8 바이트 경계에 정렬되어 있는지에 
** 4 바이트라면 [SQLITE_4_BYTE_ALIGNED_MALLOC] 컴파일시 
** 옵션이 사용됩니다. 
** 
** SQLite는 버​​전 3.5.0 및 3.5.1에​​서 정의 할 수 있었다 
내장을 일으킬 ** SQLITE_OMIT_MEMORY_ALLOCATION 
**이 루틴의 구현을 생략 할 수있게되었습니다. 기능 
** 제공되지 않습니다했습니다. 유일한 내장 메모리 할당을 사용할 수있다. 
** 
** 전에 SQLite 버전 3.7.10에는 Windows OS의 인터페이스 계층라는 
** 시스템의 malloc ()과 free ()를 직접 변환 할 때 
SQLite 때문에 사용되는 UTF-8 인코딩 사이 ** 파일 이름 
**에게 어떤 파일 이름의 인코딩 특정 Windows에서 사용되는 
** 설치. 메모리 할당 오류가 발견되었지만, 
** 이들은 [SQLITE_CANTOPEN 또는 후면보고 된 
** [SQLITE_IOERR 대신 [SQLITE_NOMEM]보다. 
** 
** [sqlite3_free () 및 sqlite3_realloc ()에 대한 포인터 인수 
전부터 여행 ** NULL 또는 다른 언젠가가 아니면 안됩니다 포인터 
가지고 [sqlite3_malloc () 또는 sqlite3_realloc ()]의 ** 호출 
** 아직 발매되지 않았다. 
** 
** 응용 프로그램은 어떤 부분을 읽거나해서는 안 
** 메모리 블록은 그것이 사용하여 해제 된 후 
** [sqlite3_free () 또는 sqlite3_realloc (). 
* /
SQLITE_API void *sqlite3_malloc(int);
SQLITE_API void *sqlite3_realloc(void*, int);
SQLITE_API void sqlite3_free(void*);

/ * 
** CAPI3REF : 메모리 할당 통계 
** 
** SQLite는 상태에보고하기 위해이 두 인터페이스를 제공 
**에서 sqlite3_malloc (), sqlite3_free ()] 및 [sqlite3_realloc () 
** 내장 메모리 할당 서브 시스템을 형성하는 루틴. 
** 
** ^ [sqlite3_memory_used () 루틴은 바이트 수를 돌려줍니다 
** 현재 미 메모리 (malloc 사가 해제되지 않습니다.) 
** ^ [sqlite3_memory_highwater () 루틴은 최대 값을 반환합니다. 
** 최고 수준 때문에 [) (sqlite3_memory_used 값 
** 마지막으로 재설정되고 있었다. ^의 값은 sqlite3_memory_used ()에 의해 돌려 주어져 
** [sqlite3_memory_highwater는 ()] 어떤 오버 헤드를 포함 
** [) (sqlite3_malloc] 구현은 SQLite에서 추가 된 
**이 오버 헤드 기본 시스템 라이브러리가 추가되지 않는다 
** [sqlite3_malloc ()를 호출 할 루틴. 
** 
** ^ 메모리 최대 수위는 현재 값으로 재설정됩니다 
** [sqlite3_memory_used ()의 경우에만 매개 변수 
** [sqlite3_memory_highwater ()가 참이다. ^ 값을 반환 
**에서 sqlite3_memory_highwater (1)] 최고 수준 인 
** 다시 전에. 
* /
SQLITE_API sqlite3_int64 sqlite3_memory_used(void);
SQLITE_API sqlite3_int64 sqlite3_memory_highwater(int resetFlag);

/ * 
** CAPI3REF : 의사 난수 생성기 
** 
SQLite는 **에 사용되는 고품질의 의사 난수 발생기 (PRNG)를 포함 
** 무작위 선택하고 ROWID를 |의 ROWID 테이블에 새 레코드를 삽입 할 때 그 
** 이미 가능한 한 최대의 ROWID] 사용하고 있습니다. PRNG는 그 밖에도 사용되는 
** 랜덤으로 빌드 ()와 randomblob () SQL 함수. 이 인터페이스는 있습니다 
** 다른 목적을 위해 동일한 PRNG에 액세스하는 애플리케이션에 이상적이다. 
** 
** ^ 버퍼 P.에 임의성이 루틴 상점 N 바이트의 호출 
** ^ N이 1보다 작 으면 P NULL 포인터 일 수있다. 
** 
** ^이 루틴은 이전에 또는 이전의 경우 호출되지 않은 경우 
** 호출 N, 1 미만의 후 PRNG는 임의성을 사용하여 배정되어 있었다 
** 기본 [sqlite3_vfs 개체의 xRandomness 메소드로부터 취득했다. 
** ^이 루틴에 대한 마지막 호출 이후 1 이상의 N이 경우 
** 의사 랜덤 수 생성 된 
** 내부에서 sqlite3_vfs] xRandomness에 의존하지 않고, 
** 방법. 
* /
SQLITE_API void sqlite3_randomness(int N, void *P);

/ * 
** CAPI3REF : 컴파일시 허용 콜백 
** 
** ^이 루틴은 특정 한 승인자의 콜백 등록 
첫 번째 인수로 지정된 ** 데이터베이스 연결. 
SQL 문이 컴파일 된 것처럼 ** ^ 승인 콜백이 호출되는 
** [sqlite3_prepare () 또는 그 변종 [sqlite3_prepare_v2 ()에서 
** [sqlite3_prepare16 () 및 sqlite3_prepare16_v2 (). ^ 각종 
** 컴파일 과정에서 포인트 논리가 생성되는대로 
** 다양한 작업을 수행하기 위해 승인자 콜백 위해 호출됩니다 
** 그 액션이 허용되어 있는지 여부를 확인합니다. ^ 승인자의 콜백을해야 
** [SQLITE_IGNORE] 허용하지 않도록 작업의 권한을 SQLITE_OK] 반환 
** 구체적인 행동이 SQL 문이 계속 가능 
** 컴파일 된 또는 SQLITE_DENY] SQL 문 전체가되게하는 
** 오류로 거부. ^ 승인자의 콜백을 반환하는 경우 
[SQLITE_IGNORE, SQLITE_OK] 또는 SQLITE_DENY] 이외의 값 ** 
트리거 ** → [sqlite3_prepare_v2 () 또는 이와 동등한 호출 
** 승인자는 오류 메시지가 표시됩니다 실패합니다. 
** 
콜백은 [SQLITE_OK] 위로와 ** 해당 작업을 의미합니다 
** 요청한 OK입니다. ^ 때 콜백 가기 SQLITE_DENY] 
트리거 ** [sqlite3_prepare_v2 () 또는 이와 동등한 호출 
** 승인자는 그것을 설명하는 오류 메시지가 표시됩니다 실패합니다 
** 액세스가 거부됩니다. 
** 
** ^ 승인자 콜백의 첫 번째 매개 변수는 세 번째 복사본입니다 
** sqlite3_set_authorizer () 인터페이스의 매개 변수입니다. ^ 두번째 매개 변수 
지정합니다 | 액션 코드 SQLITE_COPY] ** 콜백의 정수이고, 
** 특정 작업이 승인된다. ^ 6 번째 매개 변수를 통해 제 3 
** 콜백에 추가 포함 된 제로 종료 문자열입니다 
** 허용되는 작업 정보. 
** 
** ^ 액션 코드는 [SQLITE_READ]의 경우 
** 및 SQLITE_IGNORE] 콜백 가기 
** [준비된 문] 문을 대체하도록 구성되어있다 
** 있어야한다 테이블 열 대신 NULL 값 
** [SQLITE_OK가 반환 된 경우로드. [SQLITE_IGNORE] 
** 반환은 개별적으로 신뢰되지 않은 사용자의 접근을 거부하는 데 사용할 수 있습니다 
** 테이블의 열입니다. 
** ^ 액션 코드는 [SQLITE_DELETE에서 콜백이 반환되는 경우 
** [SQLITE_IGNORE] [삭제] 진행되지만, 
** [TRUNCATE 최적화는 비활성화되고 모든 행을 개별적으로 삭제됩니다. 
** 
때 ** 승인자가 사용 된 [sqlite3_prepare | 준비] 
** 신뢰할 수없는 소스에서의 SQL 문은 그 SQL 문을 보장하기 위해 
** 그렇지 않은 것을 그들이 볼 수 없습니다 데이터에 액세스하려고하는 것은 없습니다. 
** 데이터베이스를 손상 악성 문을 실행하여보십시오. 위해 
** 예를 들어, 응용 프로그램은 사용자가 임의로 입력하는 것을 허용 할 수있는 
** 데이터베이스의 평가를위한 SQL 쿼리입니다. 그러나 응용 프로그램이 수행합니다 
** 사용자가 자유롭게 변경할 수 있도록하려는 것이 아니다 
** 데이터베이스. 승인자는 그 동안 제자리에 넣을 수있는 
** 사용자가 입력 한 SQL이되는 [sqlite3_prepare | 준비라는 
** [SELECT] 문장 제외한 모든 금지합니다. 
** 
신뢰할 수없는 소스에서 SQL을 처리 할 필요가있다. ** 응용 프로그램 
**도 [sqlite3_limit를 ​​()를 사용하여 자원 제한을 낮추는 것을 검토하고 
** 및 max_page_count] [프라 그마를 사용하여 데이터베이스의 크기를 제한하는 
**인가를 사용하는 것 외에도. 
** 
** ^ (하나만 승인자는 데이터베이스 연결에서 제자리에 수 있습니다 
**시. sqlite3_set_authorizer를 호출 할 때마다 덮어 쓰게됩니다 
** 이전의 호출. ) ^ ^ NULL 콜백을 설치하여 승인자를 해제합니다. 
** 승인자는 기본적으로 비활성화되어 있습니다. 
** 
** 승인자의 콜백은 변경됩니다 아무것도 안됩니다 
승인자의 콜백을 호출 ** 데이터베이스 연결. 
** [sqlite3_prepare_v2 () 및 sqlite3_step은 () 변경 모두가 그 
이 단락에서 "변경"의 의미 ** 데이터베이스 연결. 
** 
** ^ [sqlite3_prepare_v2 ()는 문을 준비하는 데 사용되며, 
** 문장이 원인 [sqlite3_step () 중에 다시 만들어 질 수도 
** 스키마 변경. 따라서 응용 프로그램이 있는지 확인해야 
** 올바른 승인자의 콜백은 [sqlite3_step () 사이에 제자리에 남아있다. 
** 
** ^ 승인자의 콜백 만 중에 호출되는 것에주의하십시오 
** [sqlite3_prepare () 또는 그 변종. 허용하지 않습니다 
**하지 않으면 문이 평가 [sqlite3_step ()] 사이에 실행 
** 이전 단락 sqlite3_step ()를 호출에 나와있는 것처럼 
** sqlite3_prepare_v2 () 스키마 변경 후 문을 다시 준비한다. 
* /
SQLITE_API int sqlite3_set_authorizer(
  sqlite3*,
  int (*xAuth)(void*,int,const char*,const char*,const char*,const char*),
  void *pUserData
);
/ * 
** CAPI3REF : 오소 반환 코드 
** 
** [sqlite3_set_authorizer | 승인자 콜백 함수 필견 
** 차례로 [SQLITE_OK] 중 하나 돌아가거나이 두 상수 1 
** 액션이 허용되는지 여부 SQLite를 알리기 위해. 보기 
** | 추가를위한 [sqlite3_set_authorizer 승인자 문서 
** 정보. 
** 
** 그 SQLITE_IGNORE 근거하여 사용됩니다 [SQLITE_ROLLBACK | 반환 코드] 
** [sqlite3_vtab_on_conflict () 인터페이스에서. 
* /
#define SQLITE_DENY   1   /* Abort the SQL statement with an error */
#define SQLITE_IGNORE 2   /* Don't allow access, but don't generate an error */

/ * 
** CAPI3REF : 오소 액션 코드 
** 
** [sqlite3_set_authorizer () 인터페이스는 콜백 함수를 등록합니다 
** 그것은 특정 SQL 문 작업을 승인하기 위해 호출됩니다. 더 
** 콜백의 두 번째 매개 변수는 지정하는 정수 코드 
** 어떤 조치가 허용되어 있습니다. 이들은 정수 액션 코드임을 
** 승인자의 콜백을 전달해야합니다. 
** 
**이 액션 코드 값은 작업 유형이있을 수있는 의미 
** 승인했다. 별의 세 번째와 네 번째 매개 변수 
** 콜백 함수는 이러한 상관에 따라 매개 변수 또는 NULL입니다 
** 코드 번째 매개 변수로 사용됩니다. 에 ^ (다섯째 매개 변수 
** 승인자의 콜백은 데이터베이스 이름 ( "메인", "TEMP"입니다. 
** 등) 적용 가능한 경우). ^ ^ 승인자 콜백의 여섯 번째 매개 변수 
**을 담당하고 가장 안쪽의 트리거 또는 뷰의 이름입니다 
** 액세스 시도 또는 NULL이 액세스 시도가 직접적 일 
** 최상위 SQL 코드. 
* /
/******************************************* 3rd ************ 4th ***********/
#define SQLITE_CREATE_INDEX          1   /* Index Name      Table Name      */
#define SQLITE_CREATE_TABLE          2   /* Table Name      NULL            */
#define SQLITE_CREATE_TEMP_INDEX     3   /* Index Name      Table Name      */
#define SQLITE_CREATE_TEMP_TABLE     4   /* Table Name      NULL            */
#define SQLITE_CREATE_TEMP_TRIGGER   5   /* Trigger Name    Table Name      */
#define SQLITE_CREATE_TEMP_VIEW      6   /* View Name       NULL            */
#define SQLITE_CREATE_TRIGGER        7   /* Trigger Name    Table Name      */
#define SQLITE_CREATE_VIEW           8   /* View Name       NULL            */
#define SQLITE_DELETE                9   /* Table Name      NULL            */
#define SQLITE_DROP_INDEX           10   /* Index Name      Table Name      */
#define SQLITE_DROP_TABLE           11   /* Table Name      NULL            */
#define SQLITE_DROP_TEMP_INDEX      12   /* Index Name      Table Name      */
#define SQLITE_DROP_TEMP_TABLE      13   /* Table Name      NULL            */
#define SQLITE_DROP_TEMP_TRIGGER    14   /* Trigger Name    Table Name      */
#define SQLITE_DROP_TEMP_VIEW       15   /* View Name       NULL            */
#define SQLITE_DROP_TRIGGER         16   /* Trigger Name    Table Name      */
#define SQLITE_DROP_VIEW            17   /* View Name       NULL            */
#define SQLITE_INSERT               18   /* Table Name      NULL            */
#define SQLITE_PRAGMA               19   /* Pragma Name     1st arg or NULL */
#define SQLITE_READ                 20   /* Table Name      Column Name     */
#define SQLITE_SELECT               21   /* NULL            NULL            */
#define SQLITE_TRANSACTION          22   /* Operation       NULL            */
#define SQLITE_UPDATE               23   /* Table Name      Column Name     */
#define SQLITE_ATTACH               24   /* Filename        NULL            */
#define SQLITE_DETACH               25   /* Database Name   NULL            */
#define SQLITE_ALTER_TABLE          26   /* Database Name   Table Name      */
#define SQLITE_REINDEX              27   /* Index Name      NULL            */
#define SQLITE_ANALYZE              28   /* Table Name      NULL            */
#define SQLITE_CREATE_VTABLE        29   /* Table Name      Module Name     */
#define SQLITE_DROP_VTABLE          30   /* Table Name      Module Name     */
#define SQLITE_FUNCTION             31   /* NULL            Function Name   */
#define SQLITE_SAVEPOINT            32   /* Operation       Savepoint Name  */
#define SQLITE_COPY                  0   /* No longer used */
#define SQLITE_RECURSIVE            33   /* NULL            NULL            */

/ * 
** CAPI3REF : 추적 및 프로파일 링 함수 
** 
**이 루틴은 사용할 수 콜백 함수를 등록 
** 추적과 SQL 문장의 실행을 프로파일한다. 
** 
** ^ sqlite3_trace 등록한 콜백 함수는 ()에서 호출되는 
** SQL 문이 [sqlite3_step ()에서 실행되는 다양한 시간. 
** ^ sqlite3_trace () 콜백은 UTF-8로 렌더링 호출 
** 문과 SQL 문 텍스트는 먼저 실행을 시작합니다. 
** ^ (추가 sqlite3_trace () 콜백이 발생할 수 있습니다 
** 각 트리거 서브 프로그램이 입력되도록. 트리거 콜백 
** 트리거를 식별 UTF-8 SQL 주석이 포함되어 있습니다. ) ^ 
** 
** [SQLITE_TRACE_SIZE_LIMIT] 컴파일러 옵션을 제한하는 데 사용할 수있는 
** 바인딩 매개 변수 sqlite3_trace (출력 확대)의 길이. 
** 
** ^ sqlite3_profile 등록한 콜백 함수가 ()가 불려 
** 각 SQL 문이 종료되도록. ^ 프로필 콜백이 포함되어 있습니다 
** 원본 문장의 텍스트 및 시계 시간 계산 
** 명령문 실행에 걸린 시간. ^ 프로필 콜백 
** 시간,하지만 나노초 단위로 현재의 구현이다 
** 밀리 초 분해능 수있을뿐이기 때문에, 6 최하위 
** 시간의 숫자는 의미가 없습니다. SQLite는 이후 버전 
** 프로파일 러 콜백 큰 해상도를 제공 할 수 있습니다. 더 
** sqlite3_profile () 함수는 실험적으로되어있다 
**의 SQLite의 향후 버전에서 변경된다. 
* /
SQLITE_API void *sqlite3_trace(sqlite3*, void(*xTrace)(void*,const char*), void*);
SQLITE_API SQLITE_EXPERIMENTAL void *sqlite3_profile(sqlite3*,
   void(*xProfile)(void*,const char*,sqlite3_uint64), void*);

/ * 
** CAPI3REF : 쿼리의 진행 상황 콜백 
** 
** ^ sqlite3_progress_handler (D, N, X, P) 인터페이스는 콜백이 발생하는 
장시간 실행되는 동안 정기적으로 시작되는 ** 함수 X는 호출 
** [sqlite3_exec (), sqlite3_step () 및 sqlite3_get_table () 용 
** 데이터베이스 연결 D. 따라서 예제의 사용 
** 인터페이스가 큰 쿼리 중에 업데이트 GUI를 유지하는 것입니다. 
** 
** ^ 매개 변수 P는 유일한 매개 변수로 전달 된 
** 콜백 함수 X는 ^ 매개 변수 N은 대략적인 수치입니다 
연속 사이에 평가됩니다 ** 가상 머신 명령] 
만약 N이 적고 여러 진행합니다 ^ 콜백 X의 ** 호출 
** 처리기가 비활성화되어 있습니다. 
** 
** ^ 개만 진행 처리기가 시간 당 정의 할 수 
** 데이터베이스 연결; 새로운 진행 처리기를 설정하면 취소 
** 이전 1. ^ NULL 매개 변수 X를 설정하면 진행 처리기를 사용하지 않도록합니다. 
** ^ 진행 처리기 작은 N 값을 설정하여 사용할 수 있습니다 
** 1보다. 
** 
진행률 콜백이 0이 아닌 반환하면 ** ^ 작업이 
** 중단. 이 기능은 구현하는 데 사용할 수있는 
** GUI의 진행률 대화 상자의 '취소'버튼을. 
** 
** 진행 처리기 콜백 변경됩니다 아무것도 안됩니다 
** 진행 처리기를 시작하여 데이터베이스 연결. 
** [sqlite3_prepare_v2 () 및 sqlite3_step은 () 변경 모두가 그 
이 단락에서 "변경"의 의미 ** 데이터베이스 연결. 
** 
* /
SQLITE_API void sqlite3_progress_handler(sqlite3*, int, int(*)(void*), void*);

/ * 
** CAPI3REF : 새 데이터베이스 연결 열기 
** 
로 지정된 ** ^ 이러한 루틴은 SQLite 데이터베이스 파일 열기 
** filename 인수. ^ filename 인수는 UTF-8로 해석됩니다 
**에서 sqlite3_open ()와 sqlite3_open_v2 ()과 네이티브의 바이트 UTF-16 등 
** sqlite3_open16 위해 (). ^ (데이터베이스 연결 핸들은 일반적으로 
** 오류가 발생해도 * ppDb으로 돌아왔다. 유일한 예외는있다 
** SQLite는 [sqlite3의 개체를 유지하기위한 메모리를 할당 할 수없는 경우에는 
** NULL 대신 [sqlite3의]에 대한 포인터 * ppDb에 기록됩니다 
** 개체입니다. ) ^ ^ (데이터베이스가 오픈 (그리고 / 또는 생성 된 경우)에 성공 해, 그 후, 
** [SQLITE_OK가 반환됩니다. 그렇지 않은 경우 오류 코드가 반환됩니다. ) ^ ^ 
** [sqlite3_errmsg () 또는 sqlite3_errmsg16 () 루틴은 얻기 위하여 사용할 수있다 
** 중 하나가 실패 다음 오류 영어 설명 
**에서 sqlite3_open () 루틴. 
** 
** ^ 데이터베이스의 기본 인코딩은 UTF-8의 경우입니다 
**에서 sqlite3_open () 또는 sqlite3_open_v2 ()를 호출하여 
** UTF-16 sqlite3_open16 ()가 사용 된 경우 네이티브 바이트 순서. 
** 
** 오류는 그것이 개방 된 리소스가 발생하는지 여부 
** 데이터베이스 연결 핸들과 관련된 것으로 풀어 놓일 
** 그것이 불필요하게 된 때 [sqlite3_close ()에 전달하지 않습니다. 
** 
** sqlite3_open_v2 () 인터페이스로 sqlite3_open 것과 같이 작동합니다 () 
** 그것은 추가적인 제어를위한 2 개의 추가 매개 변수를 받아들이는 것을 제외하고 
** 새로운 데이터베이스 연결을 통해. ^ (flags 인자 
** sqlite3_open_v2 () 중 하나를 취할 수 있습니다 
** 어떤 조합으로도 다음 세 가지 값 
** [SQLITE_OPEN_NOMUTEX, SQLITE_OPEN_FULLMUTEX, SQLITE_OPEN_SHAREDCACHE] 
** [SQLITE_OPEN_PRIVATECACHE] 및 / 또는 [SQLITE_OPEN_URI 플래그 :) ^ 
** 
** <DL> 
** ^ (<DT> [SQLITE_OPEN_READONLY] </ DT> 
** <DD> 데이터베이스는 읽기 전용 모드로 열립니다. 데이터베이스가없는 경우 
** 이미 오류를 반환하고 존재하고 있습니다. </ DD>) ^ 
** 
** ^ (<DT> [SQLITE_OPEN_READWRITE] </ DT> 
** 데이터베이스는 읽기 가능한 경우, 쓰기 또는 읽기 위해 열린 <DD> 
** 파일이 쓰기의 운영 체제에 따라 보호되는 경우에만. 중 하나 
** 케이스는 데이터베이스가 이미 그렇지 않은 경우 오류를 반환하고 존재해야합니다. </ DD>) ^ 
** 
** ^ (<DT> [SQLITE_OPEN_READWRITE] | [SQLITE_OPEN_CREATE] </ DT> 
** <DD> 데이터베이스는 읽기와 쓰기를 위해 열린 경우에 생성되는 
** 아직도 존재하지 않는다. 이것은 항상을 위해 사용되는 동작입니다 
**에서 sqlite3_open ()와 sqlite3_open16 () </ DD>) ^ 
** </ DL> 
** 
** sqlite3_open_v2 셋째 매개 변수는 ()의 머지 않아도 아닌 경우 
** 조합은 모든 조합에 나타 
** [SQLITE_OPEN_READONLY | SQLITE_OPEN_ * 비트] 
**, 동작은 정의되지 않습니다. 
** 
** ^ [SQLITE_OPEN_NOMUTEX】 플래그가 설정되어 있으면 데이터베이스 연결 
** 한 싱글 스레드 및 멀티 스레드 스레드 모드로 열립니다 
** 모드는 컴파일시에 설정하고 시작 시간을되지 않습니다. ^ 만약 
** [SQLITE_OPEN_FULLMUTEX 플래그는 데이터베이스 연결을 연 후 설정되는 
** 직렬화 된 스레드 모드에서 싱글 스레드되지 않는 한 
** 이전에 컴파일시에 선택된하거나 시작 시간. 
** ^ [SQLITE_OPEN_SHAREDCACHE 플래그는 데이터베이스 연결이됩니다 
** 여부에 관계없이 공유의 공유 캐시 모드를 사용할 자격 
** 캐시가 sqlite3_enable_shared_cache ()를 사용하여 활성화합니다. ^ 
** [SQLITE_OPEN_PRIVATECACHE 플래그는 데이터베이스 연결이되지 않도록합니다
**이 활성화되어있는 경우에도 공유 캐시 모드에 참가하고 있습니다. 
** 
** ^ sqlite3_open_v2의 네 번째 매개 변수는 ()의 이름입니다. 
해당 운영 체제 인터페이스를 정의 ** [sqlite3_vfs 개체 
** 새로운 데이터베이스 연결을 사용해야합니다. ^ 네번째 파라미터가있는 경우 
기본 [sqlite3_vfs 개체가 사용되고있다. ** NULL 포인터. 
** 
** ^ 파일 이름이 ": 메모리 :", 그리고 민간의 임시 메모리 데이터베이스 
** 연결을 위해 만들어집니다. ^이 인 메모리 데이터베이스가 사라진다 
** 데이터베이스 연결이 닫힙니다. SQLite는 이후 버전일지도 모른다 
":"문자 **로 시작하는 추가 특수 파일 이름을 사용하고 있습니다. 
** 이것은 데이터베이스의 파일 이름이 실제로 할 때에서 시작하는 것을 권장합니다 
** A ":"문자는 다음과 같은 경로 이름을 파일 이름 접두어해야합니다 
** "/"모호함을 피하기 위해. 
** 
파일 이름이 빈 문자열의 경우 ** ^ 전용 임시 
** 디스크의 데이터베이스가 만들어집니다. ^이 개인 데이터베이스입니다 
** 즉시 자동으로 데이터베이스 연결이 닫혔로 삭제. 
** 
<H3> URI의 파일 이름 </ H3> ** [에서 sqlite3_open ()의 URI 파일 이름 
** 
** ^ 만약 [URI 파일 이름의 해석이 활성화되어 있으면 파일 이름 인수 
** "파일 :"로 시작하면 파일 이름이 URI로 해석됩니다. ^ URI를 
[SQLITE_OPEN_URI 플래그가있는 경우 ** 파일 이름의 해석이 활성화되어있는 
** ()을 sqlite3_open_v2 제 4 인수로 설정하고 그것이 있다면 
**에서 SQLITE_CONFIG_URI 옵션을 사용하여 전역 적으로 활성화되어 
** [sqlite3_config () 메서드 또는 SQLITE_USE_URI] 컴파일시 옵션. 
** SQLite 버전 3.7.7의 시점에서는 URI 파일 이름의 해석이 꺼져있는 
** 기본이 SQLite는 이후 릴리스에서 URI의 파일 이름을 사용 가능 할지도 모릅니다 
** 기본적으로 해석. 추가를 위해 "[URI 파일 이름"을 참조하십시오. 
** 정보. 
** 
** URI의 파일 이름은 RFC 3986에 따라 해석됩니다. ^ URI가 포함 된 경우 
** 권위, 그것은 빈 문자열 또는 문자열 중 하나 여야합니다 
** "localhost". ^ 당국은 빈 문자열 또는 "localhost"를,없는 경우에는 
** 오류가 호출자에게 반환됩니다. ^ URI의 fragment 컴퍼넌트 만약 
** 존재는 무시됩니다. 
** 
** ^ SQLite는 디스크 파일의 이름으로 URI의 패스 컴포넌트를 사용하고 있습니다 
** 어떤 데이터베이스가 포함되어 있습니다. ^ 경로는 '/'문자로 시작하는 경우 
** 그것은 절대 경로로 해석됩니다. ^ 경로가 시작되지 않는 경우 
** '/'(권위 섹션은 URI에서 생략 된 것을 의미한다)과 
** 경로를 상대 경로로 해석됩니다. 
** ^ Windows에서 절대 경로의 첫 번째 구성 요소 
** 드라이브 지정 (예 : "C :")이다. 
** 
** [코어 URI 쿼리 매개 변수] 
** URI의 쿼리 컴퍼넌트에 해석 된 매개 변수를 포함 할 수있다 
** SQLite는 그 자체로 또는 중 하나에 의해 [VFS | 사용자 VFS 구현]. 
** SQLite는 다음의 3 개의 쿼리 매개 변수를 해석합니다. 
** 
** <UL> 
** <LI> <B> VFS </ B> : ^ "VFS"매개 변수의 이름을 지정하는 데 사용할 수있는 
할 운영 체제 인터페이스를 제공합니다. ** VFS 객체 
** 디스크의 데이터베이스 파일에 액세스하는 데 사용된다. ^이 옵션으로 설정되어있는 경우 
** 빈 문자열은 기본 VFS 객체가 사용됩니다. ^ 미지의 지정 
** VFS는 오류가 발생합니다. ^ sqlite3_open_v2 ()를 사용하여 VFS 옵션이되어있는 경우 
** 있고 옵션으로 지정된 VFS가 더 우선합니다 
** ()을 sqlite3_open_v2의 네 번째 매개 변수로 전달 된 값입니다. 
** 
** <LI> <B> 모드 </ B> : ^ (mode 매개 변수는 어느 쪽이든 "RO", "RW"로 설정할 수 있으며, 
** "RWC"또는 "메모리" 다른 값으로 설정하려고하면있는 
** 오류) ^. 
** ^ "RO"가 지정되어있는 경우 데이터베이스가 읽기 전용으로 열립니다 
[SQLITE_OPEN_READONLY 플래그가 설정된 것처럼 ** 접근, 
** sqlite3_open_v2의 세번째 인수 (). ^ mode 옵션으로 설정되어있는 경우 
** "RW"는 데이터베이스를 읽고 쓰기 위해 열 (그러나 만들지) 된 
** 액세스는있는 것처럼 SQLITE_OPEN_READWRITE (그러나 SQLITE_OPEN_CREATE)이 있었다 
** 설정되어. ^ 값 "RWC"둘 다 설정하는 것과 동일합니다 
** SQLITE_OPEN_READWRITE과 SQLITE_OPEN_CREATE. ^ 모드 옵션이있는 경우 
** "메모리"를로드하지 않고, 순수한 [인 메모리 데이터베이스를 설정 
** 또는 디스크에서 쓰기에 사용됩니다. ^ 이것은 값을 지정하면 오류가 발생합니다 
**에서 지정된 것보다 제한된 모드 매개 변수 
** ()을 sqlite3_open_v2의 세번째 인수로 전달 된 플래그. 
** 
** <LI> <B> 캐시 </ B> : ^ 캐시 매개 변수는 "공유"로 설정하여도되고, 
** "개인" ^ "공유"로 설정하면 설정 한 경우와 동일합니다 
에 전달 된 플래그 인수 ** SQLITE_OPEN_SHAREDCACHE 비트 
** sqlite3_open_v2 (). ^ 캐시 매개 변수를 설정하는 "개인"이기 위하여 
** SQLITE_OPEN_PRIVATECACHE 비트를 설정하는 것과 같다. 
** ^ sqlite3_open_v2 ()를 사용해, 「캐시」파라미터가 중에 존재하는 경우 
** URI를 파일 이름은 그 값은 설정하여 요청 된 동작을 비활성화합니다 
** SQLITE_OPEN_PRIVATECACHE 또는 SQLITE_OPEN_SHAREDCACHE 플래그. 
** </ UL> 
** 
** ^ URI 쿼리 구성 요소의 알 수없는 매개 변수를 지정할 수는 없습니다. 
** 오류. SQLite의 이후 버전에서는 추가의 쿼리를 이해할지도 모른다 
** 매개 변수입니다. 을 위해 "[SQLite에 특별한 의미를 가진 쿼리 매개 변수"를 참조하십시오. 
** 추가 정보. 
** 
** [URI 파일 이름의 예] URI를 파일 이름의 예 <H3> </ H3> 
** 
** <table border="1" align=center cellpadding=5> 
** <TR> 번째 URI의 파일 이름은 결과를 <TH> 
** <TR> <TD> 파일 : data.db <TD> 
** 현재 디렉토리에 파일 "data.db"를 엽니 다. 
** <TR> <TD> 파일 : 홈 / 프레드 / data.db 검색 
** 파일 :/ / / 홈 / 프레드 / data.db 검색 
** 파일 :/ / localhost / 가정 / 프레드 / data.db 검색 <TD> 
** 데이터베이스 파일 "/ home / 프레드 / data.db"를 엽니 다. 
** <TR> <TD> 파일 :/ / DARKSTAR / 홈 / 프레드 / data.db <TD> 
** 오류. "DARKSTAR"권위가 없습니다. 
** <TR> <td style="white-space:nowrap"> 
** 파일 :/ / / C :/ 문서 % 20 및 % 20Settings/fred/Desktop/data.db 
** Windows의 <TD> 만 : 드라이브의 프레드 바탕 화면에 파일 열기 "data.db" 
** C :. 20이 예제에서는 이스케이프 %가 엄격하지 않는 것에주의하십시오 
** 필요한 - 공백 문자는 그대로 사용할 수 있습니다 
**의 URI 파일 이름에. 
** <TR> <TD> 파일 : data.db MODE = RO & 캐시 = 개인 <TD> 
읽기 전용 액세스를 위해 현재 디렉토리에서 ** 파일 열기 "data.db" 
** 여부에 관계없이 공유 캐시 모드 때문에 사용할 수 있습니다 
** 기본적으로 전용 캐시를 사용합니다. 
** <TR> <TD> 파일 : 홈 / 프레드 / data.db? VFS = UNIX-NOLOCK <TD> 
** 파일 열기 "/ home / 프레드 / data.db" 특별한 VFS "UNIX-NOLOCK"를 사용하십시오. 
** <TR> <TD> 파일 : data.db 모드 = 읽기 전용 <TD> 
** 오류. "읽기 전용" "모드"매개 변수의 유효한 옵션이 없습니다. 
** </ 테이블> 
** 
** ^ URI의 16 진수 이스케이프 시퀀스 (% HH)은 경로 내에서 지원되며, 
** URI의 쿼리 컴퍼넌트. 16 진수 이스케이프 시퀀스로 구성되어 있습니다 
** 백분율 기호 - "%"- 정확히 두 자리 16 진수가 계속 
** 옥텟 값을 지정한다. ^ 경로 및 쿼리 구성 요소하기 전에 
** URI의 파일 이름은 해석되고 그들은 UTF-8을 사용하여 인코딩되며 모든 
포함하는 단일 바이트로 대체 ** 16 진수 이스케이프 시퀀스 
** 해당 옥텟. 이 프로세스는 잘못된 UTF-8 인코딩을 생성하는 경우 
** 결과는 보증되지 않습니다. 
** 
** Windows 사용자에 <B> 참고 : </ B> 파일 이름 인수에 사용할 인코딩 
**에서 sqlite3_open의 ()와 sqlite3_open_v2 ()은 UTF-8이어야한다, 아니다 아무거나 
** 코드 페이지는 현재 정의되어있다. 국제가 포함 된 파일 이름 
** 문자가 전에 그들을 전달하려면 UTF-8로 변환해야합니다 
**에서 sqlite3_open () 또는 sqlite3_open_v2 (). 
** 
Windows 런타임 사용자에 ** <B> 참고 : </ b> 임시 디렉터리를 설정해야합니다 
** 앞에서 sqlite3_open () 또는 sqlite3_open_v2를 호출 (). 그렇지 않으면 다양한 
** 임시 파일의 사용을 필요로하는 기능이 실패 할 수 있습니다. 
** 
** 참조 : [sqlite3_temp_directory] 
* /
SQLITE_API int sqlite3_open(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);
SQLITE_API int sqlite3_open16(
  const void *filename,   /* Database filename (UTF-16) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);
SQLITE_API int sqlite3_open_v2(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb,         /* OUT: SQLite db handle */
  int flags,              /* Flags */
  const char *zVfs        /* Name of VFS module to use */
);

/ * 
** CAPI3REF : URI 매개 변수의 값을 가져 
** 
**이는 VFS 구현에 도움, 점검하는 유틸리티 루틴입니다 
데이터베이스 파일이 특정 쿼리가 포함 된 URI 인 경우 ** 확인 
** 매개 변수와 그 결과 쿼리 매개 변수의 값을 취득한 경우. 
** 
** 만약 F가의 XOPEN () 메서드에 전달 된 데이터베이스 파일 이름의 포인터이다 
XOPEN에 flags 매개 변수 ()가 1을 가지고 ** VFS 구현 
[SQLITE_OPEN_URI]의 **보다 또는 SQLITE_OPEN_MAIN_DB] 비트가 세트와 
** P는 쿼리 매개 변수의 이름입니다. 
** sqlite3_uri_parameter (F, P)은 P 값을 반환합니다. 
** 파라미터가 존재하는 경우 NULL 포인터 P와 같이 표시되어 있지 않은 경우 
F. 만약 P에 ** 쿼리 매개 변수는 F 쿼리 매개 변수이다 
** 명시적인 값이없는 경우 sqlite3_uri_parameter (F, P)를 돌려줍니다 
** 빈 문자열의 포인터. 
** 
** sqlite3_uri_boolean (F, P, B) 루틴은 P는 부울임을 전제로하고 있습니다 
** 매개 변수 (1) 또는 거짓 (0)의 값에 따라 true를 반환 
** P의 sqlite3_uri_boolean (F, P, B)을 반환하는 진정한 (1)의 경우 
** 쿼리 파라미터 P 값이 "그렇습니다" "진정한"중 하나, 또는 "켜짐"이다 
** 케이스 나 값이 0이 아닌 숫자로 시작하는 경우. 더 
** sqlite3_uri_boolean (F, P, B) 루틴 거짓 (0)이면 값을 반환합니다. 
** 쿼리 매개 변수 P는 어떠한 경우에도 "아니오", "가짜"또는 "OFF"중 하나 인 
** 값이 숫자 제로에서 시작하는 경우. P는 쿼리가 아닌 경우 
** F 또는 P의 값인지 매개 변수는 어느 것에도 일치하지 않는 
** 위의 경우 sqlite3_uri_boolean (F, P, B)을 반환합니다 (B! = 0). 
** 
** sqlite3_uri_int64 (F, P, D) 루틴에 p의 값을 변환 
** 64 비트 부호있는 정수와 P가없는 경우는 그 정수 또는 D를 돌려줍니다. 
** 존재하고 있습니다. P 값은 정수가 아닌 무언가 일에는 
** 제로가 반환됩니다. 
** 
F가 NULL 포인터의 경우 ** 다음 sqlite3_uri_parameter (F, P)은 NULL을 반환 
F NULL 포인터가 아닌 경우 ** sqlite3_uri_boolean (F, P, B)는 B를 반환합니다. 
** SQLite는 XOPEN에 전달 된 데이터베이스 파일의 경로 이름의 포인터가 없습니다 
** VFS 법이 루틴의 동작은 보증되지 않고, 아마 
** 바람직하지 않다. 
* /
SQLITE_API const char *sqlite3_uri_parameter(const char *zFilename, const char *zParam);
SQLITE_API int sqlite3_uri_boolean(const char *zFile, const char *zParam, int bDefault);
SQLITE_API sqlite3_int64 sqlite3_uri_int64(const char*, const char*, sqlite3_int64);


/ * 
** CAPI3REF : 오류 코드와 오류 메시지 
** 
** ^ sqlite3_errcode () 인터페이스는 수치 결과 코드를 반환하거나 
최근에 실패한 sqlite3_의 * API 호출에 대한 ** 확장 결과 코드] 
** 데이터베이스 연결에 연결된. 이전 API 호출이 실패한 경우 
에서 **이 최신 API 호출이 성공하면 반환 값 
** sqlite3_errcode ()가 정의되어 있지 않습니다. ^ sqlite3_extended_errcode () 
** 인터페이스는 항상 돌려주는 것을 제외하고 동일합니다 
** 확장 결과 코드 확장 결과 코드가있는 경우 
** 사용할 수 있습니다. 
** 
** ^ sqlite3_errmsg ()와 sqlite3_errmsg16 ()의 반환 영어 
** UTF-8 또는 UTF-16 각 하나하고, 오류를 설명하는 텍스트입니다. 
** ^ (오류 메시지 문자열을 저장하기위한 메모리가 내부적으로 관리되고있다. 
** 응용 프로그램이 결과를 풀어 놓는 것을 걱정할 필요가 없습니다. 
** 그러나 오류 문자열로 덮어 쓰거나 할당 해제 될 수 있습니다 
다른 SQLite 인터페이스 기능 ** 후속 호출. ) ^ 
** 
** ^ sqlite3_errstr () 인터페이스는 영어 텍스트를 반환합니다 
** 그것은 UTF-8로 결과​​ 코드를 설명합니다. 
** ^ (오류 메시지 문자열을 저장하기위한 메모리가 내부적으로 관리되는 
** 및 응용 프로그램에서 해방되고는한다) ^. 
** 
직렬화 된 스레드 모드가 사용중인 경우 **, 그것은 다음과 같습니다. 
번째 오류가 사이에 다른 스레드에서 발생하고있다. ** 케이스 
** 첫 번째 오류 시간과 이러한 인터페이스에 대한 호출. 
그렇게되면 ** 번째 오류는이 이후에보고됩니다 
** 인터페이스는 항상 최신의 결과를보고한다. 해결하려면 
**이 각 스레드는 데이터베이스 연결을 독점적으로 사용을 얻을 수, D 
** 시작하기 전에 [sqlite3_mutex_enter] (sqlite3_db_mutex (D))를 호출하여 
** D를 사용하면 (sqlite3_db_mutex (D)) 후 [​​sqlite3_mutex_leave] 호출 
** 여기에 언급 된 인터페이스에 대한 모든 호출이 완료하고있다. 
** 
인터페이스는 SQLITE_MISUSE에 실패하면 **는 해당 인터페이스를 의미합니다 
** 응용 프로그램이 잘못 호출했습니다. 이 경우 
** 오류 코드와 메시지가 하나 설정되지 않을 수 있습니다. 
* /
SQLITE_API int sqlite3_errcode(sqlite3 *db);
SQLITE_API int sqlite3_extended_errcode(sqlite3 *db);
SQLITE_API const char *sqlite3_errmsg(sqlite3*);
SQLITE_API const void *sqlite3_errmsg16(sqlite3*);
SQLITE_API const char *sqlite3_errstr(int);

/ * 
** CAPI3REF : SQL 문 개체 
** KEYWORDS : {준비된 명령문} {준비된 명령문} 
** 
**이 개체의 인스턴스는 단일 SQL 문을 나타냅니다. 
**이 객체는 다양하게 "준비 서」또는 A로 알려져 있습니다 
** "SQL 문을 컴파일"또는 간단히 "성명"등. 
** 
** 문 개체의 수명은 다음과 같습니다. 
** 
** <OL> 
** 사용하여 개체를 만듭니다 <LI> [sqlite3_prepare_v2을 () 또는 관련 
** 기능. 
** sqlite3_bind_ ※를 사용하여 호스트 매개 변수의 값을 바인딩 () <LI> 
** 인터페이스. 
** [sqlite3_step ()] 1 번 이상 호출하여 SQL을 실행 <LI>. 
** [) sqlite3_reset을 (] using 문을 다시 <LI>하고 다시 
** 2로 이동합니다. 이 0 번 이상 할 것. 
** [sqlite3_finalize를 ()를 사용하여 객체를 파괴 <LI>. 
** </ OL> 
** 
** 추가를위한 이상 개별 메소드의 문서를 참조하십시오. 
** 정보. 
* /
typedef struct sqlite3_stmt sqlite3_stmt;

/ * 
** CAPI3REF입니다. 런타임 제한 
** 
** ^ (이 인터페이스는 각종 구조물의 크기가 제한되는 것을 허용한다 
** 연결 기준으로 연결. 첫 번째 매개 변수가있는 
그 제한을 설정하거나 조회하는 것입니다 ** 데이터베이스 연결. 더 
** 번째 매개 변수를 정의 [리미트 범주 중 하나입니다 
** 구문 클래스는 크기가 한정되게. 세 번째 매개 변수는있다 
그 구조물에 ** 새로운 제한). ^ 
** 
새로운 제한이 음수이면 ** ^ 제한이 변경되지 않습니다. 
** ^ (각 제한 카테고리 SQLITE_LIMIT_ <I> 이름에 </ I>가 있습니다 
** [LIMITS | 하드 제한] 
**라는 C 전처리 매크로는 컴파일 중에 지정 
** [LIMITS | SQLITE_MAX_ <I> 이름 </ I>]. 
** (이름에 "_LIMIT_"는 "_MAX_"로 변경됩니다.)) ^ 
** ^ 하드 한도를 초과 제한을 늘리려 고하면 한 
** 조용히 하드 제한에서 잘. 
** 
** ^ 불구하고 제한이 변경되었는지 여부, 
** [sqlite3_limit () 인터페이스는 터미널의 이전 값을 반환합니다. 
** ^ 그래서 그것을 변경하지 않고 제한의 현재 값을 확인하려면 
** 단순히 -1로 설정 된 세 번째 매개 변수를 지정하여이 인터페이스를 호출합니다. 
** 
** 실행시 제한 사항은 관리하는 응용 프로그램의 사용을 의도하고있다 
제어되고있다. **도 모두 자신의 내부 데이터베이스 및 데이터베이스 
** 신뢰할 수없는 외부 소스에서. 샘플 응용 프로그램은 다음과 같습니다. 
기록을 저장하기 위해 자체 데이터베이스를 가지고 ** Web 브라우저 
다운로드 된 JavaScript 응용 프로그램에 의해 제어 ** 별도의 데이터베이스 
** 인터넷 할인 내부 데이터베이스를 줄 수 
** 대 기본 제한. 수있는 외부 소스에 의해 관리되는 데이터베이스 
** 서비스 거부를 방지하기 위하여 디자인 된 아주 작은 제한을주는 
** 공격. 개발자는 또한 사용하는 것이 좋습니다 [sqlite3_set_authorizer을 () 
** 더 신뢰되지 않는 SQL을 제어하기위한 인터페이스. 데이터베이스의 크기 
** 사용하여 신뢰되지 않은 스크립트에 의해 생성 수용 할 수있다 
** [max_page_count】 【PRAGMA]. 
** 
** 새로운 런타임 제한 범주는 다음 릴리스에서 추가 할 수있다. 
* /
SQLITE_API int sqlite3_limit(sqlite3*, int id, int newVal);

/ * 
** CAPI3REF : 런타임 한계 카테고리 
** KEYWORDS : {한도 카테고리} {* 리미트 카테고리} 
** 
**이 상수는 다양한 성능 제한을 정의 
즉 ** [sqlite3_limit를 ​​()를 사용하여 런타임에 저하시킬 수있다. 
** 다양한 한계의 의미를 간략 보여줍니다. 
[| SQLite 안의 한계 제한 ** 추가 정보를 얻을 수 있습니다. 
** 
** <DL> 
** [SQLITE_LIMIT_LENGTH] ^ (<DT> SQLITE_LIMIT_LENGTH </ DT> 
** 바이트 단위로 임의의 문자열이나 BLOB 또는 테이블 행의 최대 크기를 <DD>. <DD>) ^ 
** 
** [SQLITE_LIMIT_SQL_LENGTH] ^ (<DT> SQLITE_LIMIT_SQL_LENGTH </ DT> 
** SQL 문의 최대 길이는 바이트 단위로 <DD>. </ DD>) ^ 
** 
** [SQLITE_LIMIT_COLUMN] ^ (<DT> SQLITE_LIMIT_COLUMN </ DT> 
** 테이블 정의 또는 내부 열의 최대 수를 <DD> 
의 ** 결과 세트 [SELECT 또는 인덱스의 최대 열 수 
** 또는 ORDER BY 또는 GROUP BY 절에있다. </ DD>) ^ 
** 
** [SQLITE_LIMIT_EXPR_DEPTH] ^ (<DT> SQLITE_LIMIT_EXPR_DEPTH </ DT> 
** 어떤 식으로 구문 분석 트리의 최대 깊이를 <DD>. </ DD>) ^ 
** 
** [SQLITE_LIMIT_COMPOUND_SELECT] ^ (<DT> SQLITE_LIMIT_COMPOUND_SELECT </ DT> 
** 복합 SELECT 문에서 용어의 최대 수를 <DD>. </ DD>) ^ 
** 
** [SQLITE_LIMIT_VDBE_OP] ^ (<DT> SQLITE_LIMIT_VDBE_OP </ DT> 
** 가상 머신 프로그램의 명령의 최대 <DD> 
** SQL 문을 구현하는 데 사용됩니다. 이 제한은 현재 없습니다 
그것은 몇 가지 릴리스에서 추가 될지도 모르지만 ** 강제 
** SQLite는. </ DD>) ^ 
** 
** [SQLITE_LIMIT_FUNCTION_ARG] ^ (<DT> SQLITE_LIMIT_FUNCTION_ARG </ DT> 
** 기능에 인수의 최대 수를 <DD>. </ DD>) ^ 
** 
** [SQLITE_LIMIT_ATTACHED] ^ (<DT> SQLITE_LIMIT_ATTACHED </ DT> 
** 최대 <DD> 부착 | 연결된 데이터베이스. ) ^ </ DD> 
** 
** [SQLITE_LIMIT_LIKE_PATTERN_LENGTH] 
** ^ (<DT> SQLITE_LIMIT_LIKE_PATTERN_LENGTH </ DT> 
** [LIKE]에 pattern 인수의 최대 길이 <DD> 또는 
** [GLOB 연산자. </ DD>) ^ 
** 
** [SQLITE_LIMIT_VARIABLE_NUMBER] 
** ^ (<DT> SQLITE_LIMIT_VARIABLE_NUMBER </ DT> 
** SQL 문에서 어떤 매개 변수의 최대 인덱스 번호를 <DD>. ) ^ 
** 
** [SQLITE_LIMIT_TRIGGER_DEPTH] ^ (<DT> SQLITE_LIMIT_TRIGGER_DEPTH </ DT> 
** 트리거의 최대 재귀 깊이를 <DD>. </ DD>) ^ 
** </ DL> 
* /
#define SQLITE_LIMIT_LENGTH                    0
#define SQLITE_LIMIT_SQL_LENGTH                1
#define SQLITE_LIMIT_COLUMN                    2
#define SQLITE_LIMIT_EXPR_DEPTH                3
#define SQLITE_LIMIT_COMPOUND_SELECT           4
#define SQLITE_LIMIT_VDBE_OP                   5
#define SQLITE_LIMIT_FUNCTION_ARG              6
#define SQLITE_LIMIT_ATTACHED                  7
#define SQLITE_LIMIT_LIKE_PATTERN_LENGTH       8
#define SQLITE_LIMIT_VARIABLE_NUMBER           9
#define SQLITE_LIMIT_TRIGGER_DEPTH            10

/ * 
** CAPI3REF : SQL 문의 컴파일 
** KEYWORDS : {SQL 문 컴파일러} 
** 
** SQL 쿼리를 실행하려면 먼저 바이트 코드로 컴파일되어야한다 
**이 루틴 중 하나를 사용하여 프로그램. 
** 
** 첫 번째 인수 "DB"가 있기 때문 입수 한 데이터베이스 연결 
** 전에 호출이 성공 [에서 sqlite3_open (), sqlite3_open_v2 () 또는 
** [sqlite3_open16 (). 데이터베이스 연결이 종료되지는 안됩니다. 
** 
** 둘째 인수는 "ZSQL"는 encode 된 컴파일 된 문입니다 
** UTF-8 또는 UTF-16 중 하나로서. sqlite3_prepare ()와 sqlite3_prepare_v2 () 
** 인터페이스는 UTF-8을 사용하고 sqlite3_prepare16 ()와 sqlite3_prepare16_v2 () 
** UTF-16을 사용하고 있습니다. 
** 
** ^ nbyte보다 인수가 제로보다 작은 경우, ZSQL는 최대 읽기 
** 첫번째 제로의 터미네이터. nbyte보다 ^이 음수가 아닌 경우, 그것은 최대가되는 
** ZSQL에서 읽힌 바이트 수. ^ nbyte보다가 부가 아닌, 
** ZSQL 문자열은 첫 번째 '\ 000'또는 '\ U0000」의 문자 또는 중 하나로 종료 
중 먼저 ** nbyte보다 바이트 째. 호출 측이 인식하고있는 경우 
** 주어진 문자열은 NUL 종료 한 다음 작지 않아도되지 않습니다 
** 성능의 장점은 nbyte보다 매개 변수를 전달하여 얻을 수있는 것 
** </ i>를 포함하는 입력 문자열 <i> 바이트 수와 같은 
** 이러한 NUL 종료 바이트가해야한다에서 SQLite를 저장 
** 입력 문자열의 복사본을 만듭니다. 
** 
pzTail이 첫 번째 바이트를 가리 키도록 만들어져 *** ^ 만약 pzTail 다음 NULL이 아닌 
** ZSQL의 첫 번째 SQL 문 마지막 과거. 이러한 루틴 만 
** ZSQL의 첫 번째 문을 컴파일하기 위해 * pzTail은을 가리 키도록하고있다 
** 컴파일되지 않은 남아있는 것. 
** 
** ^ * ppStmt 컴파일 [준비된 문을 가르 켰다 유지되고있다 
** [sqlite3_step ()를 사용하여 실행. ^ 오류가 발생하는 경우 * ppStmt가 설정되어있다 
** NULL로. ^ 입력이 비어 있으면 입력 된 텍스트는 (NO SQL이 포함되지 않은 경우 
** 문 자열이나 의견)을 ppStmt가 NULL로 설정되어있는 *. 
** 호출 프로시 저는 컴파일 된을 제거 할 책임이있다 
** 그것으로 종료 한 후 [() sqlite3_finalize를 사용하여 SQL 문. 
** ppStmt는 NULL이 없습니다. 
** 
** ^ 성공하면 일상적인 sqlite3_prepare () 패밀리는 [SQLITE_OK] 돌려줍니다. 
그렇지 않은 경우 ** 오류 코드를 반환합니다. 
** 
** sqlite3_prepare_v2 ()와 sqlite3_prepare16_v2 () 인터페이스가 있습니다 
** 모든 새로운 프로그램에 대한 권장. 2 이전 인터페이스가 유지됩니다 
** 하위 호환성을 위해, 그러나, 그 사용은 권장되지 않습니다. 
** ^ "V2"의 인터페이스는 준비된 문 
** 그것이 반환됩니다 (sqlite3_stmt 개체)의 사본이 들어 
** 기존의 SQL 텍스트. 이것은 [sqlite3_step () 인터페이스의 원인이되는 
** 3의 방법으로 동작이 다릅니다. 
** 
** <OL> 
** <LI> 
** ^ 데이터베이스 스키마가 변경된 경우, 대신에 그것 같이 [SQLITE_SCHEMA] 회신 
** 항상하는 데 사용, sqlite3_step ()는 자동으로 SQL을 다시 컴파일합니다 
** 계산서하고 다시 실행하여보십시오. [SQLITE_MAX_SCHEMA_RETRY]​​ 가능한 한 많은 
sqlite3_step ()가 오류를 포기하고 돌아 가기 전에 ** 재 시도가 발생합니다. 
**입니다. </ li> 
** 
** <LI> 
** ^ 오류가 발생하면 sqlite3_step ()의 세부 사항 중 하나를 반환합니다. 
** 오류 코드 또는 확장 오류 코드]. ^ 기존 동작이다 것이었다 
** [sqlite3_step ()는 일반적인 [SQLITE_ERROR] 결과 코드를 반환 
** 응용 프로그램은 [sqlite3_reset ()의 두 번째 호출을해야 할 것이다 
** 문제의 근본 원인을 찾을 수 있습니다. "V2"와 조제 
** 인터페이스는 오류의 근본적인 이유는 바로 반환됩니다. 
**입니다. </ li> 
** 
** <LI> 
** ^ IF에 바인딩 된 특정 값 |에 매개 변수 host 매개 변수] 
** WHERE 절은 문장의 쿼리 계획 선택에 영향을 미칠 수 있으며, 
이 있었다 것처럼 ** 그 문은 자동으로 다시 컴파일됩니다 
변경 후 첫 [sqlite3_step () 호출 ** 스키마 변경, 
**에 | 그 매개 변수의 sqlite3_bind_text 바인딩. 
** ^ WHERE 절의 구체적인 값은 매개 변수 영향을 미칠 수 
** 쿼리 계획 선택 매개 변수는 LIKE의 왼쪽 인 경우 
** 또는 GLOB 연산자 또는 매개 변수는 인덱싱 된 열과 비교되는 경우 
** 및 SQLITE_ENABLE_STAT3] 컴파일시 옵션이 활성화되고있다. 
**입니다. </ li> 
** </ OL> 
* /
SQLITE_API int sqlite3_prepare(
  sqlite3 *db,            /* Database handle */
  const char *zSql,       /* SQL statement, UTF-8 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const char **pzTail     /* OUT: Pointer to unused portion of zSql */
);
SQLITE_API int sqlite3_prepare_v2(
  sqlite3 *db,            /* Database handle */
  const char *zSql,       /* SQL statement, UTF-8 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const char **pzTail     /* OUT: Pointer to unused portion of zSql */
);
SQLITE_API int sqlite3_prepare16(
  sqlite3 *db,            /* Database handle */
  const void *zSql,       /* SQL statement, UTF-16 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const void **pzTail     /* OUT: Pointer to unused portion of zSql */
);
SQLITE_API int sqlite3_prepare16_v2(
  sqlite3 *db,            /* Database handle */
  const void *zSql,       /* SQL statement, UTF-16 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const void **pzTail     /* OUT: Pointer to unused portion of zSql */
);

/ * 
** CAPI3REF : 검색 문 SQL 
** 
** ^이 인터페이스는 원래 저장된 복사본을 얻기 위해 사용 할 수 있습니다 
** [준비된 문을]을 만드는 데 사용되는 SQL 텍스트 그 진술이 있었을 경우는, 
** [sqlite3_prepare_v2 () 또는 sqlite3_prepare16_v2 ()] 중 하나를 사용하여 컴파일. 
* /
SQLITE_API const char *sqlite3_sql(sqlite3_stmt *pStmt);

/ * 
** CAPI3REF : SQL 문이 데이터베이스를 씁니다 여부를 판단하는 
** 
** ^ sqlite3_stmt_readonly (X)의 인터페이스는 true를 돌려줍니다 (제로가 아닌)의 경우 
[준비된 문장 X는 직접 변경하지 않습니다. **하는 경우에만 
** 데이터베이스 파일의 내용. 
** 
** 그러나 응용 프로그램 정의 SQL 함수 또는 
** 가상 테이블은 간접적으로 부작용 등의 데이터베이스를 변경하는 경우가 있습니다. 
** ^ (예를 들어, 응용 프로그램이 함수를 정의하는 경우 "eval ()"라는 
** 호출 [sqlite3_exec ()는 다음 SQL 문의 경우와 
** 부작용을 통해 데이터베이스 파일을 변경합니다. 
** 
** <BLOCKQUOTE> <PRE> 
** T2에서 ( 'T1에서 DELETE')의 eval 선택합니다. 
** </ PRE> </ BLOCKQUOTE> 
** 
** 그러나 다음 SELECT 문은 데이터베이스 파일은 변경되지 않으므로 
** 직접 sqlite3_stmt_readonly ()는 true를 돌려줍니다. ) ^ 
** 
** ^ 이런 [ROLLBACK, COMMIT, BEGIN] 같은 트랜잭션 제어문, 
** [SAVEPOINT] 및 [자료] 원인 sqlite3_stmt_readonly ()가 true를 반환하려면 
** 문장부터 자신이 실제로 데이터베이스를 변경하지 않지만, 
** 오히려 그들은 다른 문을 변경할 때의 타이밍을 제어 
** 데이터베이스. ^ 첨부 및 분리] 글도 원인 
** sqlite3_stmt_readonly () 이후 true를 반환하도록 이러한 문 사이 
** 데이터베이스 연결 설정을 변경하고 그들은하지 않습니다 
** 디스크의 데이터베이스 파일의 내용을 변경한다. 
* /
SQLITE_API int sqlite3_stmt_readonly(sqlite3_stmt *pStmt);

/ *
** CAPI3REF : 준비된 문 을 재설정 되었는지 여부를 확인
**
경우 ** ^ sqlite3_stmt_busy ( S ) 인터페이스는 ( non-zero) 가 true를 반환
** [ 준비된 문장 ] S는 사용하여 적어도 한 번 강화 되었습니다
** [ sqlite3_step ( S ) ] 가 끝까지 실행 되지 않으며 / 한 가지있다
** [ sqlite3_reset ( S ) ] 를 사용하여 재설정 되었습니다. ^ sqlite3_stmt_busy ( S )
s가 NULL 포인터 의 경우 ** 인터페이스는 false를 돌려줍니다. S가 없는 경우에는
** NULL 포인터와 올바른 [ 준비된 문 ] 에 대한 포인터 가 없습니다
** 개체는 해당 동작은 정의되지 아마도 바람직하지 않다.
**
** 이 인터페이스는 , ) ( sqlite3_next_stmt 를 함께 사용할 수있다
** 데이터베이스 에 연결된 모든 준비된 문 을 찾습니다
** 재설정 을 필요로 하는 연결 . 이것은 사용할 수 있으며,
** 예를 들어, 진단 루틴 준비 찾기
** 열린 트랜잭션 을 보유하고있는 문장 .
* /
SQLITE_API int sqlite3_stmt_busy(sqlite3_stmt*);

/ *
** CAPI3REF : 동적 타이핑 값 개체
** KEYWORDS : { 보호 된 sqlite3_value } { 보호 되지 않은 sqlite3_value }
**
** SQLite 는 모든 값을 나타내는 데 sqlite3_value 개체를 사용 하고 있습니다
** 그것은 데이터베이스 테이블 에 저장할 수 있다. SQLite 는 동적 타입 을 사용 하고 있습니다
** 값 을 위해 그것을 저장합니다. ^ sqlite3_value 객체 에 저장된 값
** 정수, 부동 소수점 값 , 문자열, BLOB 는 또는 NULL을 지정할 수 있습니다.
**
** sqlite3_value 개체는 " 보호 "또는 " 보호 되지 않은 " 의 어느 것이라 도 좋다.
** 일부 인터페이스는 보호 된 sqlite3_value 이 필요합니다. 기타 인터페이스
** 보호 또는 비보호 sqlite3_value 중 하나를 받아들입니다.
** sqlite3_value 인수 를 받아 모든 인터페이스
** 그것이 보호 된 sqlite3_value 가 필요한지 여부 .
**
** 용어는 " 보호 "와 " 보호 되지 않은 " 여부를 참조 하십시오.
** 뮤텍스가 유지 되고 있다. 내부 뮤텍스가 보호를 위해 유지 되는
** sqlite3_value 개체 하지만 누가 뮤텍스가 보호 되지 않기 때문에 유지 되지 않는다
** sqlite3_value 개체입니다. SQLite 는 단일 스레드 인 것처럼 컴파일 된 경우
** ( 및 SQLITE_THREADSAFE = 0]으로 [ sqlite3_threadsafe ( ) 0 을 반환 )
** 또는 SQLite 이 감소 뮤텍스 중 하나 의 모드 에서 실행되는 경우
** [ SQLITE_CONFIG_SINGLETHREAD 또는 SQLITE_CONFIG_MULTITHREAD ]
** 그 때 보호 되고 보호 되지 않은 사이에 구분 이 없습니다.
** sqlite3_value 개체 및 그들이 호환 으로 사용할 수있다. 그러나
** 최대 코드 이식성 을 위해 그것을 권장하는 응용 프로그램
** 아직 보호 되고 , 보호 되지 않은 구별 하기
** sqlite3_value 필요는 없습니다 경우에도 개체입니다.
**
** ^ 매개 변수로 전달됩니다 sqlite3_value 개체
** 응용 프로그램 정의 SQL 함수 의 구현은 보호 되어 있습니다.
** ^ sqlite3_value 개체 에서 반환되는
** [ sqlite3_column_value ( ) 는 보호 되지 않습니다.
** sqlite3_value 보호 되지 않는 개체 에서만 사용할 수
** [ sqlite3_result_value ( ) 및 sqlite3_bind_value ( ) .
** [ sqlite3_value_blob | sqlite3_value_type ( ) ] 패밀리
** 인터페이스는 보호 된 sqlite3_value 개체 가 필요합니다.
* /
typedef struct Mem sqlite3_value;

/ * 
** CAPI3REF : SQL 함수 컨텍스트 객체 
** 
** SQL 함수가 실행되는 컨텍스트에 저장되어있는 
** sqlite3_context 개체입니다. ^ sqlite3_context 개체에 대한 포인터 
**는 반드시 응용 프로그램 정의 SQL 함수의 첫 번째 매개 변수이다. 
** 응용 프로그램 정의 SQL 함수의 구현은 이것을 통과합니다 
** [sqlite3_result_int | sqlite3_result ()의 호출에 다니고 포인터 
** [sqlite3_aggregate_context (), sqlite3_user_data (), 
** [sqlite3_context_db_handle (), sqlite3_get_auxdata (), 
** 및 / 또는 sqlite3_set_auxdata (). 
* /
typedef struct sqlite3_context sqlite3_context;
/ *
** CAPI3REF : 준비된 문 에 바인딩 값
** KEYWORDS : { host 매개 변수 } { 호스트 매개 변수 } { 호스트 매개 변수 이름 }
** KEYWORDS : { SQL 매개 변수 } { SQL 매개 변수 } { 매개 변수가 바인딩 }
**
** ^ ( sqlite3_prepare_v2 ( ) 및 그 변종 에 대한 SQL 문 텍스트 입력 은
** 리터럴은 다음 중 하나 와 일치하는 매개 변수 로 대체 할 수있다
** 템플릿 :
**
** <UL>
** <LI> ?
** <LI> ? NNN
** <LI> : VVV
** <LI> @ VVV
** <LI> $ VVV
** < / UL >
**
** 위의 템플릿은 NNN 은 정수 리터럴 을 나타내는
** 및 VVV 는 영숫자 식별자를 나타냅니다 . ) ^ ^ 이 값
** ( 이하 " 호스트 매개 변수 이름 "또는 " SQL 매개 변수 " 라고도 함) 의 매개 변수
** 여기 에서 정의 된 sqlite3_bind_ ※ ( ) 루틴을 사용하여 설정할 수 있습니다.
**
** ^ sqlite3_bind_ ※ ( ) 루틴 의 첫 번째 인수는 항상
** [ sqlite3_stmt 개체 에 대한 포인터 에서 반환 된
** [ sqlite3_prepare_v2 ( ) 또는 그 변종 .
**
** ^ 두번째 인자 는 설정 SQL 매개 변수 의 인덱스 이다.
** ^ 왼쪽 의 SQL 매개 변수 는 1 인덱스가 있습니다. ^ 때에는 이름과 동일
** SQL 매개 변수 는 더 여러 번 눈 이후에 사용 되는
** 발생 이 최초로 출현 한 것과 같은 인덱스를 가지고있다.
** ^ 명명 된 파라미터의 인덱스는 사용하여 검색 할 수 있습니다
** [ sqlite3_bind_parameter_index ( ) API가 필요 하다면. ^ 지수
** " ? NNN " 매개 변수 의 NNN 값 입니다.
** ^ NNN 값은 [ ) sqlite3_limit ( ] 1 사이 이어야 합니다
** 매개 변수 [ SQLITE_LIMIT_VARIABLE_NUMBER ] (기본값 : 999 ) .
**
** ^ 세번째 인수 는 매개 변수에 바인딩 하는 값입니다.
** ^ 세 번째 매개 변수는 sqlite3_bind_text ( ) 또는 sqlite3_bind_text16 한 경우 ( )
** 또는 sqlite3_bind_blob ( ) NULL 포인터가 제 4 파라미터 이며,
** 는 무시되고 최종 결과는 sqlite3_bind_null ( ) 와 같다.
**
** ^ ( 네 번째 인수를 가지고 그 루틴 에서는 이 값은
** 매개 변수 의 바이트 수입니다. 명확하게 하려면 다음 의 값이됩니다
** <U> 바이트 < / U > 의 값은 문자 수 는 없습니다. ) ^
** ^ 4 번째 매개 변수 sqlite3_bind_text ( ) 또는 sqlite3_bind_text16 한 경우 ( )
** 문자열 의 길이가 음수 입니다
** 최초의 제로 종결 까지 의 바이트 수입니다.
** sqlite3_bind_blob 의 네 번째 매개 변수는 ( ) 가 부의 경우, 경우
** 동작은 미정 도리 입니다.
** 비부의 제 4 파라미터가 sqlite3_bind_text 에 제공 되는 경우 ( )
** 또는 sqlite3_bind_text16 ( ) 해당 매개 변수는 바이트 오프셋 이어야 합니다
** NUL 종결자는 문자열 이 NUL 이었다고 추정 하고 발생하는 장소
** 끝났습니다 . 모든 NUL 문자 미만 의 바이트 오프셋 에서 발생한 경우
** 네 번째 매개 변수 의 값은 결과 문자열 값은 됩니다
** 내장 NUL 이 포함되어 있습니다. 문자열 이 포함 된 식 의 결과
** 내장 NUL 에 정의 되어 있지 않습니다.
**
** ^ 다섯 번째 인수 는 ( ) sqlite3_bind_text ( ) sqlite3_bind_blob 및 TO
** sqlite3_bind_text16 ( ) 소멸자는 BLOB 를 처리 하는 데 사용 되는 하나
** SQLite 후에 문자열은 그것을 종료 했습니다. ^ 소멸자 가 호출됩니다
** 호출 ( sqlite3_bind_blob 하더라도 ) , BLOB 또는 문자열을 처리 하기,
** sqlite3_bind_text ( ) 또는 sqlite3_bind_text16 ( ) 는 실패합니다.
** ^ 5 번째의 인수가 있는 경우
** 특별한 값은 SQLITE_STATIC ]을 선택하고 SQLite 는 전제 와
** 정보 는 정적 , 비 관리 공간 에 자리한 해제 할 필요가 없습니다.
** ^ 다섯 번째 인수는 SQLITE_TRANSIENT ]을 선택하고 값을 가지고있는 경우
** SQLite 는 즉시 데이터 의 자신의 개인 복사본 이전 합니다
** sqlite3_bind_ ※ ( ) 루틴을 .
**
** ^ sqlite3_bind_zeroblob ( ) 루틴은 길이 N 의 BLOB 을 결합한다
** 는 제로 로 채워져 있다. ^ zeroblob 는 일정량 의 메모리 를 사용 하고 있습니다
** 그것이 처리 되는 동안 ( 그 크기 를 유지할만큼 의 정수 ) .
** Zeroblobs 은 BLOB 의 플레이스 홀더로서 기능 하는 것을 목적으로 하고있다
** 내용 은 후에 사용하여 작성된 것입니다
루틴 | ** 증분 BLOB I / O sqlite3_blob_open ] .
** ^ 길이 제로의 BLOB 에 zeroblob 결과 음수 .
**
** ^ sqlite3_bind_ ※ 중 하나 의 경우 는 ( ) 루틴 은 NULL로 불리고있다
** [ 준비된 문 또는 위해 준비 문장 을 사용하여
** [ sqlite3_step ( ) ] 최근 [ sqlite3_reset ( ) 보다 불리고 있었고,
** 통화가 [ SQLITE_MISUSE 가 반환 됩니다. 어떤 경우 sqlite3_bind_ ( )
** 루틴 이 확정 된 [ 준비된 문 을 , 전달
** 결과는 예측할 아마 파괴적이다.
**
** ^ 바인딩은 [ sqlite3_reset ( ) 루틴 에서 지워지지 않습니다.
** ^ 결합 하지 않은 매개 변수는 NULL로 해석 됩니다.
**
** ^ sqlite3_bind_ * 루틴은 성공했는지 의 SQLITE_OK ] 반환
** [ 오류 코드 ] 뭔가 잘못되면 .
** ^ [ SQLITE_RANGE ] 입니다 경우 매개 변수
** 인덱스가 범위를 벗어났습니다 . 의 malloc ( ) 이 실패한 경우 ^ [ SQLITE_NOMEM ] 입니다.
**
** 참조 : [ sqlite3_bind_parameter_count ( ) ,
** [ sqlite3_bind_parameter_name ( ) ] 및 [ sqlite3_bind_parameter_index ( ) .
* /
SQLITE_API int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
SQLITE_API int sqlite3_bind_double(sqlite3_stmt*, int, double);
SQLITE_API int sqlite3_bind_int(sqlite3_stmt*, int, int);
SQLITE_API int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
SQLITE_API int sqlite3_bind_null(sqlite3_stmt*, int);
SQLITE_API int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int n, void(*)(void*));
SQLITE_API int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
SQLITE_API int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
SQLITE_API int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);

/ * 
** CAPI3REF : SQL 매개 변수의 수 
** 
** ^이 루틴은 다음 SQL 매개 변수의 수를 찾는 데 사용할 수 
** [준비된 문]에있다. SQL 매개 변수는 토큰이다 
"?"** 형 '? NNN ",": AAA', '$ AAA "또는으로서의"@ AAA 등급 " 
**는 값 자리 표시 [sqlite3_bind_blob는 | 바인딩 
** 나중에 매개 변수에. 
** 
** ^ (이 루틴은 실제로는) 맨 오른쪽 (최대 인덱스를 돌려줍니다 
** 매개 변수입니다. ? NNN 이외의 모든 형태의 경우, 이것은에 해당합니다 
** 독특한 매개 변수의 수입니다. ? NNN 형태의 매개 변수가 사용되는 경우 
** 목록에 격차가 있을지도 모릅니다. ) ^ 
** 
** 참조 : [sqlite3_bind_blob | sqlite3_bind (), 
** [sqlite3_bind_parameter_name () 및 
** [sqlite3_bind_parameter_index (). 
* /
SQLITE_API int sqlite3_bind_parameter_count(sqlite3_stmt*);

/ *
** CAPI3REF : 호스트 매개 변수의 이름
**
** ^ sqlite3_bind_parameter_name ( P , N ) 인터페이스 로 돌아갑니다
** [ 준비된 문 ] 의 N 번째 의 SQL 매개 변수 의 이름 P.
** ^ ( 양식 " NNN ? " 또는 SQL 매개 변수 " : AAA '또는' @ 의 AAA 」나 「 $ AAA"
** 문자열 " NNN ? " 또는 이름이 " : AAA" 또는 " @ AAA 등급 "또는 " $ AAA" 를
** 각각.
** 즉, 첫 번째 " : " " ? "또는 " $ "또는 " @ " 또는
** 는 이름 의 일부 에 포함되어 있습니다 ) . ^
** ^ 폼 매개 변수 " ? " 다음 정수 없이 이름 이 없습니다.
** 및 " 무명 "또는 " 익명 매개 변수 " 라고.
**
** ^ 첫 번째 호스트 매개 변수가 1 의 인덱스 대신 0을 가지고 있습니다.
**
** ^ N 값이 범위 밖 또는 N 번째 파라미터가있는 경우 라면
** 이름 의 경우 NULL이 반환 됩니다. ^ 반환되는 문자열 입니다
** 항상 UTF-8 인코딩 에서 지정된 매개 변수 가있는 경우 에도
** 원래 [ sqlite3_prepare16 ( ) ] 에서 UTF- 16 또는 로 지정
** [ sqlite3_prepare16_v2 ( ) .
**
** 참조 : [ sqlite3_bind_blob | sqlite3_bind ( ) ,
** [ sqlite3_bind_parameter_count ( ) 및
** [ sqlite3_bind_parameter_index ( ) .
* /
SQLITE_API const char *sqlite3_bind_parameter_name(sqlite3_stmt*, int);
/ * 
** CAPI3REF : 지정된 이름의 파라미터의 인덱스 
** 
** ^ 그 이름 지정된 SQL 매개 변수의 인덱스를 돌려줍니다. ^ 
** 반환 된 인덱스 값은 2로 사용하기에 적합하다 
** 매개 변수 [sqlite3_bind_blob | sqlite3_bind (). ^ 제로 
일치하는 매개 변수가 없으면 ** 리턴된다. ^ 매개 변수 
** 이름은 UTF-8로 지정해야 있어도 원래의 문장 
**려면) (sqlite3_prepare16_v2를 사용하여 UTF-16 텍스트에서 준비했다. 
** 
** 참조 : [sqlite3_bind_blob | sqlite3_bind (), 
** [sqlite3_bind_parameter_count () 및 
** [sqlite3_bind_parameter_index (). 
* /
SQLITE_API int sqlite3_bind_parameter_index(sqlite3_stmt*, const char *zName);

/ * 
** CAPI3REF : 준비된 문에 모든 바인딩을 재설정 
** 
** ^ 많은 직관적 다음 sqlite3_reset는 ()은 리셋되지 않습니다 
** | [준비된 문]의 [sqlite3_bind_blob 바인딩. 
** ^ NULL로 모든 호스트 매개 변수를 재설정하려면이 루틴을 사용합니다. 
* /
SQLITE_API int sqlite3_clear_bindings(sqlite3_stmt*);
/ * 
** CAPI3REF : 결과의 열 수를 설정 
** 
** ^에서 반환 된 결과 집합의 열 수를 반환 
** [글을 준비]. ^이 루틴은 0 다시 호출은 SQL 인 경우 
** (예를 들어 새로 고침)를 데이터를 반환하지 않는 문. 
** 
** 참조 : [sqlite3_data_count을 () 
* /
SQLITE_API int sqlite3_column_count(sqlite3_stmt *pStmt);
/ *
** CAPI3REF : 결과 집합 의 열 이름
**
** ^ 이러한 루틴은 특정 열에 할당 된 이름을 반환
** [ SELECT ] 문의 결과 집합 . ^ sqlite3_column_name ( )
** 인터페이스는 0으로 종료 하는 UTF - 8 문자열 에 대한 포인터를 반환
** 와 sqlite3_column_name16 ( )는 0 종단 에 대한 포인터를 반환
** UTF - 16 문자열입니다. ^ 최초의 파라미터는 [ 준비된 문 에서
** 즉, 다음 SELECT 문을 구현하고 있습니다. ^ 두 번째 매개 변수는 있다
** 열 번호. ^ 맨 왼쪽 열 은 수 0 이다.
**
** ^ 반환 된 문자열 포인터가 준비된 문 ] 중 하나 가 될 때까지 유효합니다
문이 자동으로 될 때까지 ** [ sqlite3_finalize ( ) 에 의해 파괴 또는 되는
** 특정 실행 을위한 [ sqlite3_step ( ) 의 최초의 호출로 다시 준비
** 까지 또는 다음 의 호출
같은 열 ** sqlite3_column_name ( ) 또는 sqlite3_column_name16 ( ) .
**
** ^ 의 If sqlite3_malloc ( ) 루틴 중 하나 를 처리하는 동안 오류가 발생한
** ( UTF - 16, UTF - 8 에서 변환 중 등 ) 후
** NULL 포인터가 반환됩니다.
**
** ^ 결과 열 이름은 어구 의 'AS' 의 값 입니다
** 열 , AS 절이 있는지 . 전혀 AS 절이 없으면
** 열 이름 이 지정되어 있지 않기 때문에 변경 될 수
** 옆에 SQLite 있는 자료.
* /
SQLITE_API const char *sqlite3_column_name(sqlite3_stmt*, int N);
SQLITE_API const void *sqlite3_column_name16(sqlite3_stmt*, int N);

/ *
** CAPI3REF : 쿼리 결과 의 데이터 소스
**
** ^ 이러한 루틴은 데이터베이스 테이블 을 결정하는 수단을 제공 하고
특정 결과 란에 원점 입니다 ** 테이블 열
** [ SELECT ] 문 .
** ^ 데이터베이스 및 테이블 과 열의 이름 과 같이 반환 할 수 있습니다
** UTF - 8 또는 UTF - 16 문자열 중 하나 . ^ _database_ 루틴 은 돌아갑니다
** 데이터베이스 이름은 _table_ 루틴 은 테이블 이름 을 반환
** origin_ 루틴은 열 이름 을 반환한다.
[ 준비된 문 을 ] 소멸되기 전까지 ** ^ 반환 된 문자열 은 유효하다
** [ sqlite3_finalize 를 ( ) 를 사용하거나 문장 까지 자동으로
** 특정 실행 을위한 [ sqlite3_step ( ) 의 최초의 호출로 다시 준비
** 혹은 같은 정보가 요청 될 때까지
** 또 다른 인코딩 .
**
** ^ 반환 된 이름은 원래 비 별칭 이름입니다
** 데이터베이스 , 테이블 및 열 .
**
** ^ 이러한 인터페이스의 첫 번째 인수 는 준비 된 글 입니다.
** ^ 이 함수가 반환 N 번째 결과 열에 관한 정보를 반환
N은 두 번째 함수 의 인수 이다 ** 문장 .
** ^ 맨 왼쪽 열은 이러한 루틴 열 0 이다.
**
** ^ 문에서 반환 N 번째 열은 식 또는 있는 경우
** 하위 쿼리 및 열 값 이 아닌 경우 이러한 모든 기능은 리턴
** NULL입니다. ^ 이러한 루틴은 NULL을 반환 할 수 있는 경우 메모리 할당 오류
** 일어난다. ^ 그렇지 않으면 연결된 데이터베이스 테이블 의 이름을 반환
쿼리 결과 열이 에서 추출 되었는지 ** ​​또는 열 .
**
** ^ 다른 모든 SQLite API와 같이 이름 이 그들이 " 16 " 의 리턴으로 종료
** UTF - 16 인코딩 된 문자열 및 기타 기능은 UTF-8을 반환합니다.
**
라이브러리를 컴파일 한 경우 ** ^ 이러한 API 에만 사용할 수 있습니다
** [ SQLITE_ENABLE_COLUMN_METADATA C - 전 처리기 기호 .
**
** 두 개 이상의 스레드가 동일한 대해 이러한 루틴 중 하나 이상 을 호출하는 경우
** 하나의 구문 과 열을 준비해, 결과는
** 정의되지 않음
**
** 여러 스레드가 하나 이상의 를 호출하는 경우
** [ sqlite3_column_database_name | 열 메타 데이터 인터페이스 ]
** 같은 [ 준비된 문 ] 및 결과 열
** 동시에 , 결과는 정의되지 않습니다.
* /
SQLITE_API const char *sqlite3_column_database_name(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_database_name16(sqlite3_stmt*,int);
SQLITE_API const char *sqlite3_column_table_name(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_table_name16(sqlite3_stmt*,int);
SQLITE_API const char *sqlite3_column_origin_name(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_origin_name16(sqlite3_stmt*,int);

/ *
** CAPI3REF : 쿼리 결과 의 선언 된 데이터 형
**
** ^ ( 첫 번째 매개 변수는 준비된 문장 입니다.
** 이 문 은 SELECT ] 문과 의 n 번째 라인 인 경우
** 그것을 반환 된 결과 집합 다음 SELECT 는 테이블 의 열 ( 이 없습니다
** 식 또는 하위 질의 ) 테이블 의 선언 된 형식
** 열이 반환됩니다. ) ^ ^ 결과 집합 의 n 번째 열이있는 경우
** 식 또는 하위 쿼리는 NULL 포인터가 반환됩니다.
** ^ 반환되는 문자열 은 항상 UTF - 8로 인코딩 되어 있다.
**
** ^ ( 예를 들어, 데이터베이스 스키마 가 있다고 합니다.
**
** 테이블 T1 ( C1 돌연변이 ) 만듭니다.
**
** 및 컴파일 된 다음 글 :
**
** C1 + 1 T1 에서 C1 을 선택합니다.
**
** 이 루틴 은 두 번째 결과를 위해 문자열 " 변이 " 를 반환합니다
** 열 ( I == 1 ) 및 첫 번째 결과 컬럼 의 NULL 포인터 ( I == 0 ) ) . ^
**
** ^ SQLite 는 동적 런타임 형식 을 사용 하고 있습니다 . ^ 그래서 단순히 열
** 는 특정 유형을 포함하도록 선언 된 것을 의미 아님
** 열에 저장된 데이터 가 선언 된 형식 이다. SQLite 는 있다
** 강력한 형식 되었지만 , 타자 가 정적 또는 동적이지 않습니다. ^ 유형
** 개별 값 이 아닌 컨테이너와 연결된
** 그 값을 유지하기 위해 사용.
* /
SQLITE_API const char *sqlite3_column_decltype(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_decltype16(sqlite3_stmt*,int);

/ *
** CAPI3REF : SQL 문 에 대한
**
** [ 준비된 문 ] 중 하나를 사용 하여 제조 된 후
** [ sqlite3_prepare_v2 ( ) 또는 sqlite3_prepare16_v2 ( ) 또는 종래 의 1
** 인터페이스 [ sqlite3_prepare ( ) 또는 sqlite3_prepare16 ( ) 이 함수
** 문장 을 평가 하기 위해 1 회 이상 호출해야 합니다.
**
** sqlite3_step ( ) 의 동작 인터페이스 의 세부 사항은 다릅니다
** 문장 을 새로운 " v2 의 " 인터페이스를 사용하여 조제한 여부 에 대한
** [ sqlite3_prepare_v2 ( ) 및 sqlite3_prepare16_v2 ( ) 또는 오래된 레거시
** 인터페이스 [ sqlite3_prepare ( ) 및 sqlite3_prepare16 ( ) . 사용
** 새로운 " V2 " 인터페이스는 새로운 응용 프로그램이 레거시 를 권장합니다
** 인터페이스는 계속 지원 됩니다.
**
** ^ 레거시 인터페이스 에서는 , 반환 값은 어느 쪽이든 [ SQLITE_BUSY 이되며
** [ SQLITE_DONE , SQLITE_ROW , SQLITE_ERROR ] 또는 SQLITE_MISUSE ] .
** ^ " V2 " 인터페이스가 다른 결과 코드 중 하나
** 확장 결과 코드 뿐만 아니라 반환 할 수 있습니다.
**
** ^ [ SQLITE_BUSY 데이터베이스 엔진 이 검색 할 수 없음 을 의미합니다
** 데이터베이스 잠금 그것은 그 작업을 실행 해야 합니다. ^ 문장은 , COMMIT 인 경우
** 또는 명시 적 트랜잭션 외부에서 발생 한 다음 다시 시도 할 수 있습니다
** 계산서. 문 , COMMIT 대신 내부 에 발생하는 경우
** 명시 적 트랜잭션 당신은 전에 트랜잭션을 롤백 해야 합니다
** 계속 .
**
** ^ [ SQLITE_DONE ] 문이 종료되었음을 의미합니다
** 성공. sqlite3_step ( ) 이 가상 에서 다시 호출 해서는 없습니다
** 머신 처음 호출하지 않고 [ sqlite3_reset 을 ( ) 가상 리셋
** 초기 상태로 되돌 기계.
**
** ^ 실행 된 SQL 문이 데이터를 복원하려면 [ SQLITE_ROW ]
** 때마다 데이터 의 새 행을 통해 처리하기위한 준비가되어 있지만 반환
** 호출 . 값은 열 액세스 함수 를 사용하여 액세스 할 수있다.
** sqlite3_step ( ) 는 데이터 의 다음 행을 검색 하기 위해 다시 호출된다.
**
** ^ [ SQLITE_ERROR ] 즉, 이러한 제약 으로 런타임 오류 (
** 위반 ) 가 발생 했습니다. sqlite3_step ( ) 다시 호출 할 수 없습니다
** VM . 자세한 내용은 [ ( ) sqlite3_errmsg 를 호출하여 찾을 수있다.
** ^ 레거시 인터페이스를 통해 예를 들어, 보다 구체적인 오류 코드 ( ,
** [ SQLITE_INTERRUPT , SQLITE_SCHEMA , SQLITE_CORRUPT 등 )
** 화면에서 ) ( sqlite3_reset 를 호출함으로써 얻을 수있다
** [ 글을 준비 ] . ^ " V2 " 의 인터페이스는
** 특정 오류 코드 ) 가 sqlite3_step ( 에 의해 직접 반환됩니다.
**
** [ SQLITE_MISUSE ] 이 루틴이 잘못 호출 된 것을 의미 합니다.
** 아마 그것이 가지게 [ 준비된 문 에서 호출되었습니다
** 이미 [ sqlite3_finalize | 확정 또는 있던 1
** 이전에 [ SQLITE_ERROR ] 반품 · [ SQLITE_DONE ] . 아니면 가능성
** 동일한 데이터베이스 연결이 2 에서 사용 되기도 하고 있다고한다
** 시간에 같은 순간에 여러 스레드 .
**
** 의 SQLite 의 모든 버전 을 업 3.6.23.1 에 대한 호출을 포함
** [ sqlite3_reset 는 ( ) ] ) ( sqlite3_step 후에 필요로 아무것도 반환
** 다른 후속 호출하기 전에 [ SQLITE_ROW ] 보다
** sqlite3_step ( ) . 사용하여 준비된 문 을 재설정 하지 않으면
** [ sqlite3_reset ( ) ] 에서 [ SQLITE_MISUSE ] 수익을 가져올 것이다
** sqlite3_step ( ) . 그러나 버전 3.6.23.1 후 sqlite3_step ( ) 시작했습니다
** 호출 [ sqlite3_reset 을 ( ) 를 자동으로 상황 이 아닌
** [ SQLITE_MISUSE ] 반환 . 이것은 호환성을 고려 하지 않은
** 휴식 을 위해 지금까지 SQLITE_MISUSE 오류가 발생 모든 응용 프로그램
** 는 정의 에 의해 파괴된다. [ SQLITE_OMIT_AUTORESET ] 컴파일 시 옵션
** 레거시 동작을 복원 하는 데 사용할 수있다.
**
** 구피 인터페이스 경보 <B> : < / b > 레거시 인터페이스 에서 sqlite3_step ( )
** API는 항상 다음 [ SQLITE_ERROR , 일반적인 오류 코드를 반환
** [ SQLITE_MISUSE 및 SQLITE_BUSY 이외의 오류 . 당신이 호출 해야합니다
** [ sqlite3_reset ( ) 또는 sqlite3_finalize ( ) ] 중 하나를 찾기 위해
** 특정 오류 코드 는 더 나은 오류 를 설명한다.
** 이것은 바보 같은 디자인 임을 인정하고있다. 이 문제가 수정 되었습니다
** " V2 " 인터페이스를 가진다. 당신 의 SQL 문 을 모두 준비하면
** [ sqlite3_prepare_v2 ( ) 또는 sqlite3_prepare16_v2 ( ) ] 중 하나를 사용하여 대신
** 레거시 [ sqlite3_prepare ( ) 및 sqlite3_prepare16 ( ) 인터페이스 ,
** 더 구체적인 오류 코드 는 직접 반환됩니다
** sqlite3_step 에 의해 ( ) . " V2 " 의 인터페이스를 사용 하는 것을 권장 합니다.
* /
SQLITE_API int sqlite3_step(sqlite3_stmt*);

/ *
** CAPI3REF : 결과 집합 의 열 수
**
** ^ sqlite3_data_count ( P ) 인터페이스는 열 수를 반환합니다.
** [ 준비된 문 ] 결과 집합 의 현재 행 P.
** ^ 준비된 문 P 는 반환 된 결과에 대한 준비 가 되어 있지 않은 경우
** ( 호출 을 통해 [ sqlite3_column_int | sqlite3_column_ * ( ) 의
** 인터페이스 ) 를 sqlite3_data_count ( P ) 는 0 을 반환합니다.
p가 NULL 포인터 의 경우 ** ^ sqlite3_data_count ( P ) 루틴은 0 을 반환합니다.
** ^ sqlite3_data_count ( P) 반환 0 의 경우 이전 호출
** [ sqlite3_step ( P) [ SQLITE_DONE ] 돌아갔다. ^ sqlite3_data_count ( P )
[ sqlite3_step ( P ) 의 이전 호출이 반환 된 경우 ** 비 제로를 돌려줍니다
** [ SQLITE_ROW , 프라 그마 incremental_vacuum ] 의 경우를 제외하고
** 어디에 그것이 항상 여러 단계 의 각 단계 이후 0을 반환
** pragma는 데이터 의 0 열을 반환합니다.
**
** 참조 : [ sqlite3_column_count 을 ( )
* /
SQLITE_API int sqlite3_data_count(sqlite3_stmt *pStmt);
/ * 
** CAPI3REF : 기본 데이터 형식 
** KEYWORDS : SQLITE_TEXT 
** 
** ^ (SQLite 내의 모든 값이 5 기본 데이터 형식 중 하나입니다. 
** 
** <UL> 
** <LI> 64 비트 부호있는 정수 
** 64 비트 IEEE 부동 소수점 숫자는 <LI> 
** <LI> 열 
** <LI> 방울 
** <LI>는 NULL 
** </ UL>) ^ 
** 
**이 상수는 그 유형에 대해 코드입니다. 
** 
** SQLITE_TEXT 상수는 또한 SQLite 버전 2에서 사용했다는 것을주의하십시오 
** 완전히 다른 의미에 대해. 모두에 대해 링크 소프트웨어 
** SQLite 버전 2와 SQLite 버전 3은 SQLITE3_TEXT을하지 사용해야합니다 
** SQLITE_TEXT. 
* /
#define SQLITE_INTEGER  1
#define SQLITE_FLOAT    2
#define SQLITE_BLOB     4
#define SQLITE_NULL     5
#ifdef SQLITE_TEXT
# undef SQLITE_TEXT
#else
# define SQLITE_TEXT     3
#endif
#define SQLITE3_TEXT     3

/ *
** CAPI3REF : 쿼리 결과 에서 값
** KEYWORDS : { 열 액세스 기능 }
**
**이 루틴은 " 결과 집합 " 인터페이스를 형성 합니다.
**
** ^ 이러한 루틴은 현재 단일 열에 대한 정보를 반환
** 쿼리 의 결과 행 . ^ 두 경우 모두 첫 번째 인수는 포인터 이다
** [ 준비된 문 으로 ( 평가 되는 [ sqlite3_stmt 의 * ]
** 그것이 [ ) ( sqlite3_prepare_v2 ] 에서 반환 된 또는 그 변종 의 하나였다 )
** 2 번째 의 인수는, 어느 정보 에 대한 열의 인덱스 입니다.
** 되돌릴 필요가 있습니다. ^ 결과 집합 의 왼쪽 열의 인덱스 는 0입니다.
** ^ 결과의 열 수는 사용하여 결정할 수있다
** [ sqlite3_column_count ( ) .
**
** SQL 문 은 현재 유효한 행 을 가리 키지 않는 경우 또는
** 열의 인덱스 , 결과는 미정 도리 인 범위 를 벗어났습니다.
**이 루틴은 경우에만 최신 호출 로 호출 할 수 있습니다
** [ sqlite3_step ( ) ] [ SQLITE_ROW ] 반환되지 않으며 모두 하고있다
** [ sqlite3_reset ( ) ] 이나 [ sqlite3_finalize ( ) 계속 불리고 있습니다.
**이 루틴 중 하나 가 후에 호출 하는 경우 sqlite3_reset ( ) 또는
** [ sqlite3_finalize ( ) 또는 sqlite3_step ( )가 반환 된 후
** [ SQLITE_ROW ] 이외의 것은 , 결과는 정의되지 않습니다.
** 만약 [ sqlite3_step ( ) 또는 sqlite3_reset ( ) 또는 sqlite3_finalize ( )
** 는 다른 스레드에서 호출 되지만, 이 루틴 중 하나
** 보류되고 있지만, 그 결과는 정의되지 않습니다.
**
** ^ sqlite3_column_type ( ) 루틴이 반환
** [ SQLITE_INTEGER | 데이터 형식 코드 ] 초기 데이터 유형
** 결과 열 . ^ 반환되는 값은 SQLITE_INTEGER ] 중 하나 입니다
** [ SQLITE_FLOAT , SQLITE_TEXT , SQLITE_BLOB ] 또는 SQLITE_NULL ] . 값
** ( ) 에만 의미가 sqlite3_column_type 에 의해 반환 된 경우 형식 없음
** 변환 은 아래와 같이 발생 하고있다. 형식 변환 한 후
** sqlite3_column_type 의 반환 값은 ( ) 정의 되어 있지 않습니다. 미래
** SQLite는 버전 이 sqlite3_column_type 의 동작을 변경하려면 ( ) 수
** 형 변환 을 다음과 같이 .
**
** ^ 결과는 BLOB 또는 UTF - 8 문자열 이면, 경우 sqlite3_column_bytes ( )
** 루틴 은 BLOB 또는 문자열의 바이트 수를 반환합니다.
결과는 UTF- 16 문자열 의 경우 ** ^ 는 ( ) 로 변환 하면 sqlite3_column_bytes
** 그 때 UTF-8로 문자열과 바이트 수를 반환합니다.
** ^ 결과는 경우 sqlite3_column_bytes ( ) 를 사용하여 숫자 인 경우
** [ sqlite3_snprintf ( ) ] 의 UTF -8 문자열을 반환하고 그 값을 변환 하려면
** 문자열 의 바이트 수입니다.
결과 가 NULL의 경우 ** ^ 0을 반환 ( ) 경우 sqlite3_column_bytes .
**
** ^ 결과는 BLOB 또는 UTF-16 문자열 다음 sqlite3_column_bytes16 ( ) 인 경우
** 루틴 은 BLOB 또는 문자열의 바이트 수를 반환합니다.
** ^ 결과는 UTF-8 문자열 인 경우 에는 sqlite3_column_bytes16 ( ) 로 변환
** 그 때 UTF- 16 문자열 은 바이트 수를 반환합니다.
** ^ 결과는 ( ) 를 사용하여 sqlite3_column_bytes16 수치의 경우
** [ sqlite3_snprintf ( ) UTF- 16 문자열을 반환하고 그 값을 변환 하려면
** 문자열 의 바이트 수입니다.
결과 가 NULL의 경우 ** ^ 다음 sqlite3_column_bytes16 ( ) 는 0 을 반환합니다.
**
** ^ 의해 반환되는 값 [ 경우 sqlite3_column_bytes ( ) 및
** [ sqlite3_column_bytes16 ( ) 끝에 0 터미네이터가 포함되어 있지 않습니다
** 문자열 . ^ 명확하게 하기 위해 : 값이 반환 된다
** [ 경우 sqlite3_column_bytes ( ) 및 sqlite3_column_bytes16 ( ) 의 숫자가 있습니다
** 문자열 이 아닌 문자 의 숫자로 바이트 .
**
** ^ 문자열 ( sqlite3_column_text 에서 반환되는 ) 과 sqlite3_column_text16 ( )
** 하지만 빈 문자열 은 항상 0으로 종료 합니다. ^ 복귀
** 길이 제로의 BLOB 용 sqlite3_column_blob ( ) 에서 값이 NULL 포인터 이다.
**
** ^ 반환 개체 [ sqlite3_column_value 은 ( ) 이다
** [ 보호 되지 않은 sqlite3_value 개체 . 보호 되지 않은 sqlite3_value 개체
** 만 【 sqlite3_bind_value ( ) 와 함께 사용하여 도 좋은 [ sqlite3_result_value ( ) .
** [ 보호 되지 않은 sqlite3_value 개체 에 의해 반환 경우
** [ sqlite3_column_value ( ) 호출 을 포함한 어떤 다른 방법으로 사용 되어
** [ sqlite3_value_int ( ) 와 같은 루틴 에 [ sqlite3_value_text ( ) ,
** 또는 sqlite3_value_bytes ( ) 은 동작은 미정 도리 입니다.
**
**이 루틴은 필요한 경우 값을 변환하려고 합니다. ^ 위해
** 예를 들어 내부 표현 은 float 및 텍스트 결과 인 경우
** 이 요구되고 , sqlite3_snprintf 는 ( ) 실행 하기 위해 내부적으로 사용 되는
** 변환 을 자동으로. ^ ( 다음 표 는 변환에 대한 자세한
** 적용된다.
**
** <BLOCKQUOTE>
** <table border="1">
** <TR> 번째 내부 변환 번째 입력 브로셔 번째 요청을 입력 포토
**
** <TR> <TD> NULL 을 <TD> INTEGER <TD> 결과는 0이됩니다
** <TR> <TD> NULL 을 <TD> 결과는 0.0 이다 FLOAT <TD>
** <TR> <TD> , NULL <TD> 의 TEXT <TD> 결과는 NULL 포인터 이다
** <TR> <TD> NULL 을 <TD> BLOB <TD> 결과는 NULL 포인터 이다
** <TR> <TD> INTEGER 가 <TD> 를 떠 다니는 정수 변환 FLOAT <TD>
** 정수 <TR> <TD> INTEGER <TD> 의 TEXT <TD> 의 ASCII 표현
** <TR> <TD> INTEGER <TD> BLOB 정수 > 텍스트와 같은 <TD>
** <TR> 정수로 [ CAST ] <td> 합법적 <TD> INTEGER 플로트 <TD>
** <TR> 플로트 의 <TD> 의 TEXT <TD> 의 ASCII 렌더링 을 FLOAT <TD>
** <TR> 는 BLOB 에 <TD> 의 BLOB <TD> [ CAST ] 을 FLOAT <TD>
<TD> ** <TR> <TD> 의 TEXT <TD> 은 INTEGER INTEGER 에 [ CAST ]
** <TR> <TD> TEXT 는 실물에 <TD> [ CAST ] 을 FLOAT <TD>
** <TR> <TD> 의 TEXT <TD> 방울 <TD> 변경 은 없습니다
INTEGER 에서 ** <TR> <TD> BLOB <TD> INTEGER <TD> [ CAST ]
** <TR> <TD> BLOB 이 실물 에 <TD> [ CAST ] 을 FLOAT <TD>
필요한 경우 ** <TR> <TD> 의 BLOB <TD> 의 TEXT 제로 터미네이터 를 추가 <td> 정당
** < / 테이블 >
** < / BLOCKQUOTE > ) ^
**
** 위의 표는 표준 C 라이브러리 함수 atoi 함수를 참조하는 ( )
** 와 atof 함수 ( ) . SQLite 는 정말 이러한 함수를 사용 하지 않습니다. MFR190/2.16 는
** 자신 의 상응하는 내부 루틴 . 는 atoi ( ) 와 atof 함수 ( ) 이름은
그들은 대부분 에 익숙 하기 때문에 ** 간결하게하기 위해 테이블 에서 사용되는
** C 프로그래머 .
**
** 형 변환 이 발생하면 포인터가 앞에서 됨을 주의 하십시오
** sqlite3_column_blob 호출 ( ) sqlite3_column_text ( ) 및 / 또는
** sqlite3_column_text16 ( ) 은 비활성화 되어 있다.
** 형식 변환 , 포인터를 무효화 가 발생할 수 있습니다
** 다음과 같은 경우 :
**
** <UL>
** <LI> 초기 콘텐츠는 BLOB 및 sqlite3_column_text ( ) 또는
** sqlite3_column_text16 ( ) 가 호출됩니다. 제로 터미네이터 마이트
** 문자열 에 추가 될 필요가 있다. 한 < / li >
** <LI> 초기 콘텐츠는 UTF-8 텍스트와 sqlite3_column_bytes16 ( ) 또는
** sqlite3_column_text16 ( ) 가 호출됩니다. 내용 은 변환 해야 합니다
** 하는 UTF - 16. 있습니다. < / li >
** <LI> 초기 콘텐츠 는 UTF- 16 텍스트와 경우 sqlite3_column_bytes ( ) 또는
** sqlite3_column_text ( ) 가 호출됩니다. 내용 은 변환 해야 합니다
** UTF-8로 . 한 < / li >
** < / UL >
**
** ^ UTF - 16BE 및 UTF - 16LE 간의 변환은 항상 장소에서 행해져 관광 하는
** 사전 포인터를 무효로 하지 않지만, 물론 버퍼의 내용
** 전 포인터 참조가 변경 되는 것. 다른 종류의
** 변환 은 그들은 때로는 그것이 가능할 때 , 장소에서 이루어 지지만 ,
** 은 불가능하며, 그런 경우 에 사전 포인터가 무효화 됩니다.
**
** 정책을 기억 가장 안전하고 가장 쉽게 이러한 루틴 을 호출 할 수 있다
** 다음 중 하나 의 방법으로 :
**
** <UL>
** <LI> sqlite3_column_text ( ) ) ( 경우 sqlite3_column_bytes 이어졌다 < / li >
** 경우 sqlite3_column_bytes 계속 <LI> 의 sqlite3_column_blob ( ) ( ) < / LI >
** <LI> 의 sqlite3_column_text16 ( ) sqlite3_column_bytes16 계속 ( ) < / LI >
** < / UL >
**
** 즉, 당신이 ) ( sqlite3_column_text 를 호출해야 ,
결과를 강제 ** sqlite3_column_blob ( ) 또는 sqlite3_column_text16 ( ) 첫 번째
** 원하는 형식으로 변환하고 ( ) 를 호출하면 sqlite3_column_bytes 또는
** sqlite3_column_bytes16 ( ) 결과 의 크기를 찾을 수 있습니다. 호출 을 혼합하지 마십시오
에 ** sqlite3_column_text ( ) 또는 sqlite3_column_blob ( ) 의 호출
** sqlite3_column_bytes16 ( ) 및 ( sqlite3_column_text16 에 대한 호출을 혼합하지 마십시오 )
** 경우 sqlite3_column_bytes ( ) 의 호출 .
**
형식 변환 과 같이 발생할 때까지 ** ^ 반환 포인터 가 유효한지
** 위 또는 될 때까지 sqlite3_step ( ) 또는 sqlite3_reset ( ) 또는
** [ sqlite3_finalize 은 ( ) 라고 있습니다. ^ 메모리 공간은 문자열을 저장 하는 데 사용
** 및 BLOB 는 자동으로 해제 됩니다. b는 하지 < / b> 반환 된 포인터를 전달할 것
** 에서 sqlite3_column_blob ( ) , sqlite3_column_text ( ) ] 등에
** [ sqlite3_free ( ) .
**
** ^ ( 메모리 할당 오류가 하나 평가 발생한 경우
**이 루틴 의 경우 기본값 이 반환됩니다. 기본값
** 정수 0 부동 소수점 숫자 0.0 또는 NULL 중 하나입니다
** 포인터 . [ sqlite3_errcode ( ) 에 대한 후속 호출이 반환됩니다
** [ SQLITE_NOMEM ). ^
* /
SQLITE_API const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_bytes(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);
SQLITE_API double sqlite3_column_double(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_int(sqlite3_stmt*, int iCol);
SQLITE_API sqlite3_int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
SQLITE_API const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
SQLITE_API const void *sqlite3_column_text16(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_type(sqlite3_stmt*, int iCol);
SQLITE_API sqlite3_value *sqlite3_column_value(sqlite3_stmt*, int iCol);

/ *
** CAPI3REF : 준비 문 개체를 파괴 하는
**
** ^ sqlite3_finalize ( ) 함수는 준비된 문 을 제거 하기 위해 호출됩니다.
** ^ 글 에 대한 최근 평가 에 오류가 발생하지 않은 경우
문이 평가 된 것은 없다 되는 경우 ** ? 그리고 ( ) 가 복귀 를 sqlite3_finalize
** SQLITE_OK . ^ 문장 에 대한 최근 평가 가 실패한 S 경우
** sqlite3_finalize ( S)는 적절한 오류 코드 를 반환 하거나
** 오류 코드를 확장 .
**
** ^ sqlite3_finalize ( S ) 루틴 중 언제든지 호출 할 수 있습니다
** [ 준비된 문 ] S 라이프 사이클 :
** 문장 S가 지금까지 평가 되기 전에 나중에
[ sqlite3_reset ( ) 에 ** 1 이상 호출 또는 후에 어떤 통화
** 에 [ sqlite3_step ( ) 에 관계없이 문이 있는 여부
** 실행을 완료 했다.
**
** ^ NULL 포인터가 sqlite3_finalize ( ) 를 호출하면 무해한 아무것도 하지 않습니다.
**
** 응용 프로그램을 해결 하기 위해 모든 [ 준비된 문 을 확정해야 합니다
** 리소스 누수 . 이것은 사용 하고자하는 응용 프로그램 을위한 비참한 오류
** 그것이 확정 된 후 준비 된 문 . 제조 된 임의 사용
** 그것이 확정 된 후 문은 정의되지 않은 결과 라고 할 수 있습니다
** 이러한 세그먼트 오류 및 힙 손상 등 의 바람직하지 않은 행동 .
* /
SQLITE_API int sqlite3_finalize(sqlite3_stmt *pStmt);

/ *
** CAPI3REF : 준비 문 개체를 재설정
**
** sqlite3_reset ( ) 함수가 준비된 문장 을 재설정 하기 위해 호출됩니다
** 재실행 될 준비가 초기 상태로 되돌아 개체 .
** ^ 값을 사용하여 그들을 결합 된 임의의 SQL 문 변수
** [ sqlite3_bind_blob | sqlite3_bind_ ※ ( ) API ] 값을 유지합니다.
** 바인딩을 재설정 하려면 [ sqlite3_clear_bindings 를 ( ) 를 사용 합니다.
**
** ^ [ sqlite3_reset ( S ) ] 인터페이스는 , 준비된 문장 ] S 재설정
** 축소 프로그램 의 시작 부분에 .
**
** ^ 만약 위하여 [ sqlite3_step ( S ) ] 에 최근 호출
** [ 준비된 문장 ] S는 [ SQLITE_ROW 또는 SQLITE_DONE ] 반환
** 또는 sqlite3_step ( S ) ] 는 지금까지없는 S 에 불려 가고있는 경우
** → [ sqlite3_reset ( S ) ] 의 [ SQLITE_OK 을 반환합니다.
**
** ^ 만약 위하여 [ sqlite3_step ( S ) ] 에 최근 호출
** [ 준비된 문장 ] S는 오류를 나타
** [ sqlite3_reset ( S ) ] 는 적절한 오류 코드 를 반환합니다.
**
** ^ [ sqlite3_reset ( S ) ] 인터페이스는 값은 변경 되지 않습니다
** 중 하나 의 sqlite3_bind_blob | 바인딩 ] [ 준비된 문 으로 S.
* /
SQLITE_API int sqlite3_reset(sqlite3_stmt *pStmt);

/ *
** CAPI3REF : 만들거나 SQL 함수 를 다시 정의
** KEYWORDS : { 함수 작성 루틴 }
** KEYWORDS : { 응용 프로그램 정의 SQL 함수 }
** KEYWORDS : { 응용 프로그램 정의 SQL 함수 }
**
** ^ ( 통칭하여 " 함수 작성 루틴 " 라고도 함 ) 이 함수
** 은 SQL 함수 또는 집계 를 추가하거나 동작을 다시 정의 하는 데 사용 되는
** 기존 의 SQL 함수 또는 집계 . 사이의 유일한 차이점
**이 루틴은 예상되는 텍스트 인코딩 이다
** 번째 매개 변수 ( 작성중인 함수 의 이름 )
** 와 소멸자 콜백 의 존재 또는 부재
** 응용 프로그램 데이터 의 포인터 .
**
** ^ 첫 번째 매개 변수는 데이터베이스 연결 은 앞의 SQL 입니다
** 기능이 추가 된다. ^ 응용 프로그램은 여러 데이터베이스를 사용하는 경우
** 연결 하여 응용 프로그램 정의 SQL 함수를 추가 해야 합니다
** 개별적으로 각 데이터베이스 연결 에 .
**
** ^ 두번째 매개 변수는 만드는 SQL 함수 의 이름이나 입니다
** 다시 정의 했습니다. ^ 이름 의 길이는 UTF-8 에서 255 바이트로 제한 되어 있습니다
** 제로 터미네이터 의 독점적 인 표현. ^ 그러나 이름
** 길이 의 제한 은 UTF - 8 바이트가 아닌 문자도 UTF- 16 바이트 입니다.
** ^ 긴 이름 의 함수를 만들려고 하면
** [ SQLITE_MISUSE ] 반환 할 수 있습니다.
**
** ^ 세 번째 매개 변수 ( NARG )
** 인수의 수가 있는 SQL 함수 또는
** 집계 걸립니다. ^ 이 매개 변수 가 -1의 경우, SQL 함수 또는 있는 경우
** 집계 는 0 과 한계 사이에서 임의의 수의 인수를 취할 수
** [ sqlite3_limit ] ( SQLITE_LIMIT_FUNCTION_ARG )에서 설정 되었다. 만약 셋째
** 매개 변수가 -1 보다 작거나 127 보다 크게 다음 의 행동 이다
** 정의되지 않음
**
** ^ 4 번째 매개 변수 eTextRep 는 지정된 어떤
** [ SQLITE_UTF8 | 텍스트 인코딩 이 SQL 함수 는 에 대한 선호
** 매개 변수 . 응용 프로그램은 이 매개 변수를 설정 해야 합니다
** [ SQLITE_UTF16LE ] 만약 함수 의 구현 이 호출
** 입력 의 sqlite3_value_text16le ( ) 또는 SQLITE_UTF16BE ] 의 경우
** 구현 이 호출 [ sqlite3_value_text16be 을 ( ) 입력 또는
** [ SQLITE_UTF16 ] [ sqlite3_value_text16 는 ( ) 를 사용 또는 SQLITE_UTF8 ] 의 경우
** 하지 않다 . ^ 동일한 SQL 함수를 사용하여 여러 번 등록되어 있는 경우가
에 대한 다른 구현 ** 다른 바람직한 텍스트 인코딩
** 각 코딩.
** ^ 동일한 기능 의 여러 구현 이 가능 하다 SQLite는
** 데이터 변환 의 최소 금액을 필요로하는 무슨 을 선택합니다.
**
** ^ 4 번째 매개 변수는 필요에 따라 [ SQLITE_DETERMINISTIC 및 OR 됩니다
** 함수 가 항상 주어진 동일한 결과를 반환 함을 알리기 위해
** 단일 SQL 문에서 같은 입력 . 대부분의 SQL 함수
** 확실히 . 내장 임의 ( ) SQL 함수 의 예입니다
** 명확하지 않는 기능 . SQLite 의 쿼리 planner 는 할 수 있습니다
** 결정적 추가 최적화 를 수행 , 그 사용
** [ SQLITE_DETERMINISTIC 플래그 의 가능한 권장 합니다.
**
** ^ ( 번째 매개 변수는 임의 의 포인터 이다. 구현
** 함수 [ ( ) sqlite3_user_data 을 ] ) ^ 사용하여 포인터 에 대한 액세스를 얻을 수 있습니다
**
** ^ 여섯 일곱 번째, 8 번째 매개 변수는 xFunc , XSTEP 과 xFinal 는 있다
SQL 함수 또는 을 구현하는 C 언어 함수 포인터 **
** 집계 . ^ 스칼라 SQL 함수는 xFunc 를 구현 해야 합니다
** 콜백은 널 포인터 XSTEP 과 xFinal 과 로 전달 해야합니다
** 매개 변수입니다. ^ 집계 SQL 함수는 XSTEP 를 구현 해야 합니다
** 와 xFinal 로 NULL 포인터 가 xFunc 을 위해 통과해야 합니다. ^ 기존 을 제거하려면
** SQL 함수 또는 집계는 모든 3 개의 기능 에 NULL 포인터를 전달
** 콜백 .
**
** ^ ( sqlite3_create_function_v2 하는 아홉 번째 매개 변수 ( ) 가 NULL이 아닌 경우
** 그것은 응용 프로그램 데이터 포인터 의 소멸자 이다.
기능이 제거 된 때 ** 소멸자 있음 중 하나로 시작 되는
데이터베이스 연결이 닫힐 때 ** 오버로드 되었는가? ) ^
** ^ 소멸자 도 호출되면 호출
** sqlite3_create_function_v2 ( ) 는 실패합니다.
** ^ 10 번째 매개 변수 의 소멸자 콜백이 호출되면
** 응용 프로그램 데이터의 사본 인 단일 인수가 전달됩니다
** sqlite3_create_function_v2 의 다섯 번째 매개 변수 ( ) 였다 포인터입니다.
**
** ^ 그것은 같은 여러 구현을 등록 하는 것을 허용한다
** 기능 과 동일한 이름 을 가지고 있지만 다른 숫자 중 하나 에서
** 인수 또는 다른 텍스트 인코딩 . ^ SQLite 는 사용됩니다
** 가장 정확한 방법 과 일치하는 구현 팬
** SQL 함수 가 사용 된다. ^ 비부 가 가지는 기능 의 구현
** NARG 매개 변수가 있는 함수 의 구현 보다 일치 합니다
** 네거티브 NARG . ^ 기능 어디에 텍스트 인코딩
** 데이터베이스 encode 방식이 뛰어나다 고 일치하는
** 인코딩이 다르게 행동 일치합니다.
** ^ 인코딩 차이가 UTF16le 과 UTF16BE 사이의 기능
** 인코딩 차이가있는 기능 보다 가까운 성냥 이다
** UTF8 및 UTF16 사이 .
**
** ^ 내장 함수는 새로운 애플리케이션 정의 함수 다중 정의 할 수있다.
**
** ^ 애플리케이션 정의 함수는 다른 사람을 호출 할 권한이 있다
** SQLite 인터페이스 . 그러나 이러한 호출 해서는 안됩니다
** 데이터베이스 연결을 닫을 준비 를 확정 또는 재설정
** 계산서 어떤 함수가 실행 되는 동안.
* /
SQLITE_API int sqlite3_create_function(
  sqlite3 *db,
  const char *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*)
);
SQLITE_API int sqlite3_create_function16(
  sqlite3 *db,
  const void *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*)
);
SQLITE_API int sqlite3_create_function_v2(
  sqlite3 *db,
  const char *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*),
  void(*xDestroy)(void*)
);

/ * 
** CAPI3REF : 텍스트 인코딩 
** 
**이 상수는 다양한을 나타내는 정수 코드를 정의하는 
**의 SQLite에서 지원되는 텍스트 인코딩입니다. 
* /
#define SQLITE_UTF8           1
#define SQLITE_UTF16LE        2
#define SQLITE_UTF16BE        3
#define SQLITE_UTF16          4    /* Use native byte order */
#define SQLITE_ANY            5    /* Deprecated */
#define SQLITE_UTF16_ALIGNED  8    /* sqlite3_create_collation only */

/ * 
** CAPI3REF : 기능 플래그 
** 
**이 상수는 함께 OR 연산 된 
** [SQLITE_UTF8 | 원하는 텍스트 인코딩 넷째 인수로 
** [sqlite3_create_function ()]에서 [sqlite3_create_function16 () 또는 
** [sqlite3_create_function_v2 (). 
* /
#define SQLITE_DETERMINISTIC    0x800
/ * 
** CAPI3REF : 사용되지 않는 함수 
** 비추천 
** 
**이 기능은 [비추천]하고있다. 유지하기 위해 
** 기존 코드와의 호환성은 이러한 함수는 계속 
**지지를 받고있다. 그러나 새 응용 프로그램에서는 피해야합니다 
**이 함수의 사용. 해결하기 위해 사람들을 격려 지원하는 
**이 함수를 사용하여 우리는 그들이 무엇을 해야할지 말할 생각은 없습니다. 
* /
#ifndef SQLITE_OMIT_DEPRECATED
SQLITE_API SQLITE_DEPRECATED int sqlite3_aggregate_count(sqlite3_context*);
SQLITE_API SQLITE_DEPRECATED int sqlite3_expired(sqlite3_stmt*);
SQLITE_API SQLITE_DEPRECATED int sqlite3_transfer_bindings(sqlite3_stmt*, sqlite3_stmt*);
SQLITE_API SQLITE_DEPRECATED int sqlite3_global_recover(void);
SQLITE_API SQLITE_DEPRECATED void sqlite3_thread_cleanup(void);
SQLITE_API SQLITE_DEPRECATED int sqlite3_memory_alarm(void(*)(void*,sqlite3_int64,int),
                      void*,sqlite3_int64);
#endif

/ *
** CAPI3REF : 가져 SQL 함수 매개 변수 값
**
** SQL 함수 의 C 언어 구현 은 용도 를 집계
** 인터페이스 루틴 이 집합은 매개 변수 값 에 액세스하기위한
** 함수 또는 집계 .
**
** ( 라 함수 의 경우 ) xFunc 또는 XSTEP ( 집계 용 ) 매개 변수
** 에 [ sqlite3_create_function ( ) 및 sqlite3_create_function16 ( )
** SQL 함수 또는 집계 를 구현하는 콜백 을 정의합니다.
**이 콜백 의 제 3 인수는 포인터 의 배열 에
** 개체 [ sqlite3_value 보호 . 를위한 1 sqlite3_value 개체가 있습니다
** SQL 함수 의 각 매개 변수입니다. 이러한 루틴은 사용 되는
** [ sqlite3_value 개체 에서 값을 꺼낸다.
**
**이 루틴은 보호 된 sqlite3_value 개체 에서만 작동 합니다.
** [ 보호 되지 않은 sqlite3_value 에서 이러한 루틴 을 사용하려고 하면
정의되지 않은 동작 ** 개체 의 결과 .
**
** ^ 이러한 루틴 은 단순히 해당 열 액세스 기능 처럼 작동
**이 루틴 은 하나의 보호 된 sqlite3_value 를 취하는 것을 제외하고 개체
** 포인터 대신 [ sqlite3_stmt * ] 포인터와 정수 열 번호.
**
** ^ sqlite3_value_text16 ( ) 인터페이스는 UTF - 16 문자열을 추출하고
** 호스트 시스템 의 네이티브의 바이트 순서에서 . ^
** sqlite3_value_text16be ( ) 와 sqlite3_value_text16le ( ) 인터페이스
** 추출물, UTF - 16 문자열로 빅 엔디안 과 리틀 엔디안 였다.
**
** ^ ( sqlite3_value_numeric_type ( ) 인터페이스는 적용 하려고
** 값 에 숫자 의 친화력 . 이것은 시도 가 있다는 것을 의미
** 정수 또는 부동 소수점 값을 변환 하기 위해 만들었습니다. 만약
** 이러한 변환은 그렇지 ( 정보 의 손실없이 가능하다
** 기간 값이 숫자 처럼 보이는 문자열 의 경우 )
** 변환이 수행 된다. 그렇지 않으면 변환 되지 않습니다.
** [ SQLITE_INTEGER | 데이터 형식 . 변환 이 반환 된 후 ) ^
**
** 포인터를 반환 사실 에 특히주의 하십시오
** 에서 sqlite3_value_blob ( ) , sqlite3_value_text ( ) 또는
** [ sqlite3_value_text16 ( ) 에 대한 후속 호출에 의해 비활성화 할 수 있습니다
** [ sqlite3_value_bytes ( ) , sqlite3_value_bytes16 ( ) , sqlite3_value_text ( ) ,
** 또는 sqlite3_value_text16 ( ) .
**
**이 루틴은 동일한 스레드 로 호출 해야 합니다
** [ sqlite3_value * 매개 변수를 공급 SQL 함수 .
* /
SQLITE_API const void *sqlite3_value_blob(sqlite3_value*);
SQLITE_API int sqlite3_value_bytes(sqlite3_value*);
SQLITE_API int sqlite3_value_bytes16(sqlite3_value*);
SQLITE_API double sqlite3_value_double(sqlite3_value*);
SQLITE_API int sqlite3_value_int(sqlite3_value*);
SQLITE_API sqlite3_int64 sqlite3_value_int64(sqlite3_value*);
SQLITE_API const unsigned char *sqlite3_value_text(sqlite3_value*);
SQLITE_API const void *sqlite3_value_text16(sqlite3_value*);
SQLITE_API const void *sqlite3_value_text16le(sqlite3_value*);
SQLITE_API const void *sqlite3_value_text16be(sqlite3_value*);
SQLITE_API int sqlite3_value_type(sqlite3_value*);
SQLITE_API int sqlite3_value_numeric_type(sqlite3_value*);

/ *
** CAPI3REF : 집계 함수 의 컨텍스트를 가져
**
** 집계 SQL 함수 의 구현 은이를 사용
** 의 상태를 저장 하기위한 메모리를 할당 루틴 .
**
** ^ sqlite3_aggregate_context ( C , N ) 루틴이 처음 호출 될 때
** 특정 집계 함수는 SQLite 의
** 메모리 N 개의 를 할당하고 그 메모리 를 제로로 포인터를 반환
** 새로운 메모리 . ^ 눈 후속 호출
** 같은 집계 함수 인스턴스 의 sqlite3_aggregate_context ( )
** 동일한 버퍼가 반환됩니다. Sqlite3_aggregate_context ( ) 는 일반적으로
** XSTEP 콜백이 호출 될 때마다 한 번 불린 후 1
** xFinal 및 콜백이 호출 된 마지막 시간. ^ ( NO 의 경우 행이 일치 하지 않습니다
** 집계 쿼리 XSTEP ( ) 집계 함수 의 콜백
** 구현이 호출 되는 것은 아니며 , xFinal 와 ( ) 가 한 번만 호출됩니다.
** 이런 경우 에는 sqlite3_aggregate_context ( ) 을 촉구 될지도 모른다
** xFinal 와 내부에서 처음 ( ) . ) ^
**
** ^ sqlite3_aggregate_context ( C , N ) 루틴 NULL 포인터를 반환합니다.
N은 제로 이하 거나 같으면 먼저 호출 ** 때 메모리
** 할당 오류가 발생합니다.
**
** ^ ( ( C , N sqlite3_aggregate_context 의해 할당 된 공간 의 양 ) 가있다
** 첫 번째 호출이 성공 하는데있어서, N 개의 매개 변수 에 의해 결정 . 변화
** sqlite3_aggregate_context 에 대한 후속 호출 ( ) 에서 n 의 값
** 같은 집계 함수 인스턴스 메모리 의 크기를 변경할 수 없습니다
** 배급. ) ^ xFinal 및 콜백 내에서 설정할 수 통례 이다
** sqlite3_aggregate_context 의 호출은 N = 0 ( C , N )가되도록 없다
** 무의미 메모리 할당 이 발생합니다.
**
** ^ SQLite 는 자동으로 할당 된 메모리를 해제 합니다
** sqlite3_aggregate_context ( ) 집계 쿼리 가 끝납니다.
**
** 최초의 파라미터는 복사 해야 합니다
** [ sqlite3_context | SQL 함수 컨텍스트 첫 번째 매개 변수 임을
** 집계를 구현 XSTEP 또는 xFinal 및 콜백 루틴 에
** 기능 .
**
** 이 루틴은 내의 동일한 스레드 에서 호출 해야 합니다
** 집계 SQL 함수 가 실행되고 있습니다.
* /
SQLITE_API void *sqlite3_aggregate_context(sqlite3_context*, int nBytes);

/ * 
** CAPI3REF : 함수의 사용자 데이터 
** 
** ^ sqlite3_user_data () 인터페이스는 복사본을 반환합니다 
** pUserData 매개 변수 인 포인터 (다섯 번째 매개 변수) 
**에서 sqlite3_create_function () 
** 및 sqlite3_create_function16 () 루틴이 원래 
** 응용 프로그램 정의 함수를 등록했습니다. 
** 
**이 루틴은 내의 동일한 스레드에서 호출해야합니다 
** 응용 프로그램 정의 함수가 실행되고 있습니다. 
* /
SQLITE_API void *sqlite3_user_data(sqlite3_context*);
/ * 
** CAPI3REF : 함수 데이터베이스 연결 
** 
** ^ sqlite3_context_db_handle () 인터페이스는 복사본을 반환합니다 
** 데이터베이스 연결에 대한 포인터 (제 1 파라미터) 
**에서 sqlite3_create_function () 
** 및 sqlite3_create_function16 () 루틴이 원래 
** 응용 프로그램 정의 함수를 등록했습니다. 
* /
SQLITE_API sqlite3 *sqlite3_context_db_handle(sqlite3_context*);
/ *
** CAPI3REF : 기능 보조 데이터
**
**이 함수는 ( 비 집계 ) SQL 함수를 사용 하여도된다
** 인수 의 값을 연결할 메타 데이터 . 동일한 값을 전달 하는 경우
쿼리 아래 에 동일한 SQL 함수 ** 여러 호출
** 어떤 상황 은 연결된 메타 데이터 가 저장 되어 있다. 예
** 이 도움이 될 수도 위치 정규식 매칭 이다
** 기능 . 정규식 의 컴파일 된 버전 으로 기억 될 수있다
** 패턴 문자열 에 대한 메타 데이터 .
** 계속되고있는 한 패턴 문자열이 같다면 ,
** 컴파일 된 정규식은 여러 에서 재사용 할 수 있습니다
** 같은 함수 를 호출합니다.
**
** ^ sqlite3_get_auxdata ( ) 인터페이스는 메타 데이터 에 대한 포인터를 반환
** N 번째 인수를 가지는 sqlite3_set_auxdata ( ) 함수 와 관련
** 응용 프로그램 정의 함수 에 값 . ^ 메타 데이터가 없는 경우
** 함수 의 인수 와 관련된 이 sqlite3_get_auxdata ( ) 인터페이스
** NULL 포인터를 반환합니다.
**
** ^ sqlite3_set_auxdata ( C , N , P , X ) 인터페이스 가 N 번째 메타 데이터로 P 를 절약 할
** 응용 프로그램 정의 함수 의 인수 . ^ 그럼
** 최신 에서 ( C , N) 반환 P 를 sqlite3_get_auxdata 통화
** sqlite3_set_auxdata ( C , N , P , X ) 를 호출 메타 데이터 가 유효 이거나
** NULL 메타 데이터가 삭제 된 경우 .
** ^ 각 호출은 sqlite3_set_auxdata 후 ( C , N , P , X ) 는 X가 NULL 이 아닌,
** SQLite 는 매개 변수 P와 소멸자 함수 X를 시작합니다 정확하게
** 메타 데이터 가 삭제되는 일단 한다.
<UL> : ** SQLite 는 포함하여 언제든지 메타 데이터를 삭제 하고 자유 롭다
** <LI> 와 해당 함수 의 매개 변수 를 변경하거나
** [ sqlite3_reset ( ) 또는 sqlite3_finalize 은 ( ) 에 대한 호출 <LI>
** SQL 문 또는
sqlite3_set_auxdata ( ) 가 같은 파라미터 로 재차 불려 상표입니다. ** <LI> 때
** 기존 sqlite3_set_auxdata 동안 <LI> ( ) 를 호출하면 메모리
** 할당 오류가 발생합니다. < / UL > ) ^
**
** 특히 마지막 총알을 참고 하십시오. 중간 소멸자 X
** sqlite3_set_auxdata ( C , N , P , X ) 를 전에 빨리 불릴지도 모른다
** sqlite3_set_auxdata ( ) 인터페이스 도 반환됩니다. 따라서 sqlite3_set_auxdata ( )
** 함수 의 구현 의 끝 부분 에 호출 될 때 해야한다
** 함수 의 구현은 후 , P 중 하나를 이용해야 이 없습니다.
** sqlite3_set_auxdata ( ) 를 호출 합니다.
**
** ^ ( 사실, 메타 데이터는 함수간에 저장 되어 있기 때문에 호출
리터럴을 포함하는 컴파일 타임 상수 이며, ** 함수 매개 변수
** 값과 매개 변수 와 동일한 갖춰진 표현. ) ^
**
**이 루틴은 내의 동일한 스레드 에서 호출 해야 합니다
** SQL 함수 가 실행되고 있습니다.
* /
SQLITE_API void *sqlite3_get_auxdata(sqlite3_context*, int N);
SQLITE_API void sqlite3_set_auxdata(sqlite3_context*, int N, void*, void (*)(void*));


/ * 
** CAPI3REF : 상수 정의 특별한 소멸자 동작 
** 
**이은으로 전달되는 소멸자위한 특수 값입니다 
** [sqlite3_result_blob ()와 같은 루틴의 마지막 인수. ^ 만약 소멸자 
** 인수가 SQLITE_STATIC에서 콘텐츠 포인터가 일정하다는 것을 의미 
** 변경하는 것은 아닙니다. 그것은 파괴 할 필요가 없습니다. ^ 
** SQLITE_TRANSIENT 값은 내용이 이렇게 변경하는 것을 의미합니다 
** 가까운 장래에 그 SQLite는 자신의 사적인 카피를해야한다 
** 가기 전에 내용. 
** 
** 유형 정의는 특정 문제를 해결하는 것이 필요하다 
** C + + 컴파일러. 
* /
typedef void (*sqlite3_destructor_type)(void*);
#define SQLITE_STATIC      ((sqlite3_destructor_type)0)
#define SQLITE_TRANSIENT   ((sqlite3_destructor_type)-1)

/ *
** CAPI3REF : SQL 함수 의 결과 설정
**
**이 루틴은 xFunc 또는 xFinal 및 콜백 에서 사용되는
** SQL 함수 또는 집계를 구현 합니다. 보기
** [ sqlite3_create_function ( ) 및 sqlite3_create_function16 ( )
** 자세한 내용은 .
**
**이 함수는 많은 매개 변수 바인딩 가족처럼 동작
** 함수는 준비된 문의 매개 변수 를 호스트 하기 위해 값을 바인딩 하는 데 사용 된다.
** 자세한 내용은 SQL 매개 변수 설명서를 참조 하십시오.
**
** ^ sqlite3_result_blob ( ) 인터페이스 에서 결과를 설정합니다
** 응용 프로그램 정의 함수는 그 내용이 뾰족한 BLOB 이기 위하여
** 번째 매개 변수 와 그에 따라 하게 n은 N 바이트 의 길이 이다
** 세 번째 매개 변수입니다.
**
** ^ sqlite3_result_zeroblob ( ) 인터페이스는 결과 집합
** 응용 프로그램 정의 함수 가 모두 제로 를 포함 BLOB 이기 위하여
** N은 두 번째 매개 변수 의 값 이다 크기, 바이트 및 N 바이트 .
**
** ^ sqlite3_result_double ( ) 인터페이스 에서 결과를 설정합니다
** 응용 프로그램 정의 함수는 지정된 부동 소수점 값 이기 위하여
** 그 두번째 인자 에 의한 다.
**
** ^ sqlite3_result_error ( ) 와 sqlite3_result_error16 ( ) 함수
** 구현 SQL 함수 에서 예외가 발생 하는 원인이 됩니다.
** ^ SQLite 는 에서 가리키는 문자열을 사용 합니다
** 둘째 sqlite3_result_error 매개 변수 ( ) 또는 sqlite3_result_error16 ( )
** 오류 메시지 의 텍스트로 . ^ SQLite 는 오류 를 해석
** sqlite3_result_error 에서 메세지 문자열 ( ) 은 UTF-8로 . ^ SQLite는
** UTF - 16 의 네이티브 처럼 ) ( sqlite3_result_error16 에서 문자열을 해석 하는
** 바이트 순서 . ^ 세 번째 매개 변수 가 sqlite3_result_error 한 경우 ( )
** 또는 sqlite3_result_error16 ( ) 가 부의 그리고 SQLite 는 오류로 취
** 최초의 제로 문자를 통해 메시지 의 모든 텍스트를 향합니다.
** ^ 3 번째 매개 변수는 ( ) 를 sqlite3_result_error 할 경우
** sqlite3_result_error16 ( ) 음수 가 아니 SQLite 는 걸린다는 많은
** 오류 메시지로 두 번째 매개 변수 에서 바이트 ( 문자 는 아니다) .
** ^ sqlite3_result_error ( ) 와 sqlite3_result_error16 ( )
** 루틴은 오류 메시지 텍스트 의 이전 개인 복사본을 만들
** 그들은 다시 . 따라서 함수 호출 은 할당 해제 또는 수 있습니다
** 그들은 피해없이 귀국 후에 텍스트를 변경합니다.
** ^ sqlite3_result_error_code ( ) 함수는 오류 코드를 변경하려면
** 함수 의 오류 의 결과로 SQLite 에 반환된다. ^ 기본적으로
** 오류 코드 는 SQLITE_ERROR 입니다. ^ sqlite3_result_error 에 대한 후속 호출 ( )
** 또는 sqlite3_result_error16 ( ) 는 SQLITE_ERROR 오류 코드를 재설정합니다.
**
** ^ sqlite3_result_error_toobig ( ) 인터페이스는 SQLite 가 발생 하는 원인이 될
** 문자열이나 BLOB 표현 하려면 너무 길다는 것을 나타내는 오류 .
**
** ^ sqlite3_result_error_nomem ( ) 인터페이스는 SQLite 가 발생 하는 원인이 될
** 메모리 할당 이 실패 했음을 나타내는 오류 .
**
** ^ sqlite3_result_int ( ) 인터페이스는 반환 값 을 설정합니다
** 응용 프로그램 정의 함수 의 32 비트 부호있는 정수로
** 제 2 인수로 주어진 값 .
** ^ sqlite3_result_int64 ( ) 인터페이스는 반환 값 을 설정합니다
** 응용 프로그램 정의 함수 의 64 비트 부호있는 정수로
** 제 2 인수로 주어진 값 .
**
** ^ sqlite3_result_null ( ) 인터페이스는 반환 값 을 설정합니다
** 응용 프로그램 정의 함수 NULL입니다 .
**
** ^ sqlite3_result_text ( ) sqlite3_result_text16 ( )
** sqlite3_result_text16le ( ) 및 sqlite3_result_text16be ( ) 인터페이스
** 응용 프로그램 정의 함수 의 반환 값은 되도록 설정
** UTF - 8 과 같이 표현 텍스트 문자열은 UTF - 16은 네이티브의 바이트 순서 ,
** UTF - 16 리틀 엔디안 또는 UTF - 16 빅 엔디안 였다.
** ^ SQLite 는 응용 프로그램 에서 텍스트 결과를 가지고
** sqlite3_result_text * 인터페이스 의 두 번째 매개 변수입니다.
** ^ 만약 sqlite3_result_text * 인터페이스 의 제 3 인수
** 음수 인 경우, SQLite 는 두 번째 매개 변수 에서 결과 텍스트를 가지고
** 최초의 제로 문자 통해서.
** ^ 만약 sqlite3_result_text * 인터페이스 의 제 3 인수
** 텍스트 의 부가 아닌 경우 바이트 (문자 단위 아님) 입니다.
** 둘째 매개 변수가 가리키는 는 다음과 같이 가지고 응용 프로그램 정의
** 함수 의 결과 . 세 번째 매개 변수 가 부가 아닌 , 그것 일
** 문자열 에 대한 바이트 오프셋 이어야 합니다 어디에 NUL 종결 것이다
** 널 문자 로 끝나는 문자열인지 나타난다. 모든 NUL 문자 가 발생한 경우
** 그것을 바이트 오프셋 문자열 에서 세 번째 값보다 작은
** 매개 변수는 결과 문자열이 포함 된 NUL은 과 가 포함되어 있습니다
** 내장 NUL 을 포함하는 문자열 에서 작동 식 의 결과는 부정 입니다.
** ^ 만약 sqlite3_result_text * 인터페이스 의 네 번째 매개 변수
** 또는 sqlite3_result_blob 가 NULL 포인터 인 경우, SQLite 는 것을 호출
** 그것이 가지고있는 텍스트 또는 BLOB 결과 에 소멸자 역할을
** 그 결과를 이용하여 완성했습니다.
** ^ 만약 sqlite3_result_text * 인터페이스 또는 의 네 번째 매개 변수
** sqlite3_result_blob 특별한 상수 SQLITE_STATIC , SQLite 입니다
** 텍스트 또는 BLOB 의 결과가 아닌 일정한 공간 에 위치해 하지 않는 것을 전제로하고 있습니다
** 매개 변수 의 내용을 복사 하거나 콘텐츠 에 소멸자 를 호출
** 그것이 그 결과를 이용하여 종료 했을 때.
** ^ 만약 sqlite3_result_text * 인터페이스 의 네 번째 매개 변수
** 또는 sqlite3_result_blob 특별한 상수 SQLITE_TRANSIENT 입니다
** 그리고 SQLite 는 에서 얻은 공간 에 결과 의 복사본을 만듭니다
** 에서 sqlite3_malloc ( ) ] 가 가기 전에.
**
** ^ sqlite3_result_value ( ) 인터페이스는 결과 를 설정
** 응용 프로그램 정의 함수는 복사 되도록
둘째 매개 변수 로 지정된 ** [ 보호 되지 않은 sqlite3_value 개체 . ^
** sqlite3_result_value ( ) 인터페이스는 [ sqlite3_value ] 의 복사본을 만듭니다
** [ sqlite3_value 매개 변수 로 지정된 변경하거나 할 수 있도록
** 피해없이 sqlite3_result_value ( ) 가 복귀 한 후 할당 을 해제 한다.
** ^ [ 보호 된 sqlite3_value 개체가 항상 사용 되지 수있다
** [ 보호 되지 않은 sqlite3_value 개체가 그 중 하나 , 필요로 되는
** 유형 의 sqlite3_value 개체 는이 인터페이스를 사용할 수 있습니다.
**
**이 루틴은 다른 스레드 에서 호출 된 경우
** 받은 응용 프로그램 정의 함수를 포함하는 것보다는
** [ sqlite3_context ] 포인터 , 결과는 정의되지 않습니다.
* /
SQLITE_API void sqlite3_result_blob(sqlite3_context*, const void*, int, void(*)(void*));
SQLITE_API void sqlite3_result_double(sqlite3_context*, double);
SQLITE_API void sqlite3_result_error(sqlite3_context*, const char*, int);
SQLITE_API void sqlite3_result_error16(sqlite3_context*, const void*, int);
SQLITE_API void sqlite3_result_error_toobig(sqlite3_context*);
SQLITE_API void sqlite3_result_error_nomem(sqlite3_context*);
SQLITE_API void sqlite3_result_error_code(sqlite3_context*, int);
SQLITE_API void sqlite3_result_int(sqlite3_context*, int);
SQLITE_API void sqlite3_result_int64(sqlite3_context*, sqlite3_int64);
SQLITE_API void sqlite3_result_null(sqlite3_context*);
SQLITE_API void sqlite3_result_text(sqlite3_context*, const char*, int, void(*)(void*));
SQLITE_API void sqlite3_result_text16(sqlite3_context*, const void*, int, void(*)(void*));
SQLITE_API void sqlite3_result_text16le(sqlite3_context*, const void*, int,void(*)(void*));
SQLITE_API void sqlite3_result_text16be(sqlite3_context*, const void*, int,void(*)(void*));
SQLITE_API void sqlite3_result_value(sqlite3_context*, sqlite3_value*);
SQLITE_API void sqlite3_result_zeroblob(sqlite3_context*, int n);

/ *
** CAPI3REF : 새로운 조합 순서를 정의
**
** ^ 이러한 기능 의 추가, 삭제 또는 데이터 를 변경 관련
** 데이터베이스 연결에서 첫 번째 인수로 지정되어 있습니다.
**
** ^ 데이터 정렬 이름은 UTF-8 문자열 이다
** sqlite3_create_collation 용 ( ) 와 sqlite3_create_collation_v2 ( )
** 와 sqlite3_create_collation16 ( ) 에 대한 네이티브 바이트 순서 UTF- 16 문자열입니다.
[ sqlite3_strnicmp ( ) ] 에 따르면 동일하다고 ** ^ 조합 이름 은
** 같은 이름이라고 생각됩니다 .
**
** ^ ( 세 번째 인수 ( eTextRep ) 가 상수 중 하나 여야 합니다
** <UL>
** <LI> [ SQLITE_UTF8 ]
** <LI> [ SQLITE_UTF16LE ]
** <LI> [ SQLITE_UTF16BE ]
** <LI> [ SQLITE_UTF16 또는
** <LI> [ SQLITE_UTF16_ALIGNED ] .
** < / UL > ) ^
** ^ eTextRep 인수가 전달 된 문자열 의 인코딩을 결정
** 데이터 함수 콜백 에 xCallback .
** ^ eTextRep 위해 [ SQLITE_UTF16 및 SQLITE_UTF16_ALIGNED 값
** 힘 문자열은 네이티브의 바이트 순서에서 UTF16 한다.
** ^ 시작 eTextRep 힘 문자열 에서 SQLITE_UTF16_ALIGNED 값
** 짝수 바이트 주소 .
**
** ^ 네 번째 인수 PARG 는 전달 된 응용 프로그램 데이터 의 포인터 이다
** 통해 데이터 함수 콜백 의 첫 번째 인수로 .
**
** ^ 다섯 번째 인수 xCallback 는 데이터 정렬 함수 에 대한 포인터 이다.
** ^ 여러 데이터 기능은 동일한 이름을 사용하여 등록 할 수 있습니다 만,
** 다른 eTextRep 매개 변수 와 SQLite 때문에 사용하는 것이
** 기능은 데이터 변환 의 필요성이 가장 적습니다.
xCallback 인수가 null 의 경우 ** ^ 그리고 데이터 함수 이다
** 삭제 . ^ 동일한 이름의 모든 조합 기능 이 삭제 된 경우
** 해당 데이터 를 사용할 수 없게됩니다.
**
** ^ 데이터 함수 콜백은 PARG 복사 로 불려
** 응용 프로그램 데이터 포인터와 지정된 인코딩 의 두 캐릭터 라인을 가지는
** eTextRep 인수 에 의한 다. 데이터 함수는 반환해야 합니다
**, 부의 제로 또는 정의 정수
** 첫 번째 문자열 이 두 번째 같음 , 미만 또는 큰 경우
** 각각. 데이터 함수는 항상 같은 대답 을 반환해야 합니다
** 같은 입력 을 줬다. 두 개 이상의 데이터 기능은 등록 된 경우
** 동일한 데이터 정렬 이름 ( 다른 eTextRep 값을 사용하여 ) 모든
동일한 문자열 로 불려 갔을 때 ** 상응하는 응답을 제공해야 합니다.
** 데이터 함수는 모든 속성을 다음과 같이 따라야 한다
** 문자열 A , B, C :
**
** <OL>
** <LI> 만약 == B 이후 B == A 에서
** <LI> 경우 == B 와 B == C 다음 == 로
** <LI> 경우 <B THEN B> A.
** <LI> 만약 A < B 와 B < C는 A < C.
** < / OL >
**
** 데이터 기능은 이러한 제한 중 하나와 그 실패했을 경우
SQLite 의 ** 기능을 조합 하면 등록 된 사용 후 행동
** 이 정의 되어 있지 않습니다.
**
** ^ sqlite3_create_collation_v2 는 ( ) sqlite3_create_collation 것과 같이 작동합니다 ( )
** xDestroy 콜백이 PARG 에서 호출 되었는지 를 추가 할 때
** 데이터 기능이 제거 됩니다.
이들은 나중에 덮어 쓴 경우 ** ^ 데이터 기능이 제거 됩니다
** 데이터 생성 함수 를 호출하거나
** [ 데이터베이스 연결 ] [ ) ( sqlite3_close 를 사용하여 닫혀 있다.
**
** ^ xDestroy 콜백 이 있으면 불리는 < / U > 가 아닌 <u> 의 거야
** sqlite3_create_collation_v2 ( ) 함수는 실패합니다. 시작 응용 프로그램
** sqlite3_create_collation_v2 ( ) 가 null 이외 xDestroy 인수를 지정 해야한다
** 반환 코드 를 검사하여 응용 프로그램 데이터 의 포인터를 처분
** 자신 이 아니라 그들을 위해 그것을 다루는 것을 기대 SQLite는 .
** 이것은 다른 모든 SQLite 인터페이스와 다릅니다. 모순
** 유감스러운 일입니다 만, 후방 깨지 않고 변경할 수 없습니다
** 호환 .
**
** 참조 : [ sqlite3_collation_needed ( ) 및 sqlite3_collation_needed16 ( ) .
* /
SQLITE_API int sqlite3_create_collation(
  sqlite3*, 
  const char *zName, 
  int eTextRep, 
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*)
);
SQLITE_API int sqlite3_create_collation_v2(
  sqlite3*, 
  const char *zName, 
  int eTextRep, 
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*),
  void(*xDestroy)(void*)
);
SQLITE_API int sqlite3_create_collation16(
  sqlite3*, 
  const void *zName,
  int eTextRep, 
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*)
);

/ *
** CAPI3REF : 데이터 필요한 콜백
**
** ^ 데이터베이스 전에 모든 데이터 정렬을 등록하는 것을 피하기 위해
** 사용할 수있는 단일 콜백 함수는 에서 등록 할 수있다
** 데이터베이스 연결 호출 될 때마다 정의되지 않은 데이터
** 시퀀스 가 필요 합니다.
**
** ^ 기능은 sqlite3_collation_needed ( ) API를 사용하여 등록되어 있는 경우
** 그것은 문자열로 정의 되지 않는 데이터 정렬 의 이름이 전달됩니다
** UTF-8로 인코딩 된 . ^ sqlite3_collation_needed16 ( ) 가 사용되는 경우
** 이름 은 UTF -16 시스템의 원시 바이트 순서 처럼 전달됩니다.
** ^ 두 함수 를 호출하면 기존 데이터 필요한 콜백 을 바꿉니다.
**
콜백이 호출 될 때 ** ^ ( 전달 된 첫 번째 인수 는 복사 본인
** 2 번째 의 인수 sqlite3_collation_needed ( ) 또는
** sqlite3_collation_needed16 ( ) . 두 번째 인수는 데이터베이스 입니다
** 연결 . 세 번째 인수는 SQLITE_UTF8 , SQLITE_UTF16BE ] 중 하나 입니다
** 또는 SQLITE_UTF16LE , 데이터 의 가장 바람직한 형태 를 나타내는
** 시퀀스 기능 이 필요합니다. 네 번째 매개 변수 의 이름입니다.
** 필요한 데이터 정렬 . ) ^
**
** 콜백 함수 를 사용 하여 원하는 데이터 를 등록 해야 합니다
** [ sqlite3_create_collation ( ) , sqlite3_create_collation16 ( ) 또는
** [ sqlite3_create_collation_v2 ( ) .
* /
SQLITE_API int sqlite3_collation_needed(
  sqlite3*, 
  void*, 
  void(*)(void*,sqlite3*,int eTextRep,const char*)
);
SQLITE_API int sqlite3_collation_needed16(
  sqlite3*, 
  void*,
  void(*)(void*,sqlite3*,int eTextRep,const void*)
);

#ifdef SQLITE_HAS_CODEC
/ * 
** 암호화 된 데이터베이스를위한 키를 지정합니다. 이 루틴은 있어야 
**에서 sqlite3_open 직후라는 (). 
** 
**이 API를 구현하는 코드는 공개 릴리스에서는 사용할 수 없습니다. 
**의 SQLite는. 
* /
SQLITE_API int sqlite3_key(
  sqlite3 *db,                   /* Database to be rekeyed */
  const void *pKey, int nKey     /* The key */
);
SQLITE_API int sqlite3_key_v2(
  sqlite3 *db,                   /* Database to be rekeyed */
  const char *zDbName,           /* Name of the database */
  const void *pKey, int nKey     /* The key */
);

/ * 
** 오픈 데이터베이스의 키를 변경합니다. 현재 데이터베이스가없는 경우에는 
** 암호화 된이 루틴은 그것을 암호화합니다. 만약 PNEW == 0 또는 n 새 == 0, 
** 데이터베이스는 해독됩니다. 
** 
**이 API를 구현하는 코드는 공개 릴리스에서는 사용할 수 없습니다. 
**의 SQLite는. 
* /
SQLITE_API int sqlite3_rekey(
  sqlite3 *db,                   /* Database to be rekeyed */
  const void *pKey, int nKey     /* The new key */
);
SQLITE_API int sqlite3_rekey_v2(
  sqlite3 *db,                   /* Database to be rekeyed */
  const char *zDbName,           /* Name of the database */
  const void *pKey, int nKey     /* The new key */
);
/ * 
** SEE 데이터베이스 활성화 키를 지정합니다. 아니면 
** 활성화를 참조하십시오 루틴의 아무도 작동하지 않습니다. 
* /
SQLITE_API void sqlite3_activate_see(
  const char *zPassPhrase        /* Activation phrase */
);
#endif

#ifdef SQLITE_ENABLE_CEROD
/*
** Specify the activation key for a CEROD database.  Unless 
** activated, none of the CEROD routines will work.
*/
SQLITE_API void sqlite3_activate_cerod(
  const char *zPassPhrase        /* Activation phrase */
);
#endif

/ * 
** CAPI3REF : 단시간 실행을 중단 
** 
** sqlite3_sleep () 함수는 현재 스레드가 실행을 중지시키고 
**이 매개 변수로 지정된 밀리 세컨드 단위의 최소 수에 대해. 
** 
** 운영 체제는 자고 요청을 지원하지 않는 경우 
** 밀리 초 시간 해상도는 시간이 반올림됩니다 
** 가장 가까운 초. 실제로 수면 시간 (밀리 초) 
** 운영 체제에서 요청이 반환된다. 
** 
** ^ SQLite는 xSleep를 호출하여이 인터페이스를 구현하고 있습니다 () 
** 기본 [sqlite3_vfs 개체의 메서드. 만약 xSleep () 메서드 
** 기본 VFS가 제대로 구현되지 않았거나 구현되지 않습니다 
** 모든 후 sqlite3_sleep () 동작 설명에서 일탈 할 수있다 
** 이전 단락에서. 
* /
SQLITE_API int sqlite3_sleep(int);

/ *
** CAPI3REF : 폴더 지주 임시 파일 이름
**
** ^ ( 이 전역 변수 가 있는 문자열을 가리 키도록 이루어진 경우
** 폴더 의 ​​이름 ( 별명 디렉토리 ) 의 경우 모든 임시 파일
** 내장 사용시에는 SQLite 에서 만든 [ sqlite3_vfs 일 | VFS ]
** 해당 디렉토리 에 배치 됩니다. ) ^ ^ 경우이 변수
** NULL 포인터 인 경우, SQLite 는 적절한 검색을 실시해,
** 임시 파일 디렉토리 .
**
** 이것은 여러 에서 이 변수를 읽거나 변경해도 안전 하지 않습니다
** 당시 스레드. 이것은 이 변수를 읽거나 변경해도 안전 하지 않습니다
** 데이터베이스 연결 은 별개로 동시에 사용 되는 경우
** 스레드 .
** 또한 이 변수가 한번 설정 되도록 설계 되어 있다
** 프로세스 초기화 의 일환으로 모든 SQLite 인터페이스 전에
** 루틴이 호출되고 ,이 변수는 변경 되지 않습니다 것을
** 다음 .
**
** ^ [ temp_store_directory pragma는 이 변수와 원인을 해결 할 수있다
** 그것은 [ sqlite3_malloc ] 에서 가져온 메모리 를 가리 키도록 설정합니다. ^ 또한
** [ temp_store_directory 프라 그마 ] 항상 전제 와 임의의 문자열
** 이 변수 포인트 는 메모리에 저장 되어 있는 것과는 여행
** [ sqlite3_malloc ] 및 pragma는 해당 메모리를 해제 하려고 시도 할 수있다
** [ sqlite3_free ] 사용.
이 변수가 직접 변경된 경우 ** 따라서 중 하나 이어야 합니다
** NULL을 하거나 , sqlite3_malloc ] 에서 가져온 메모리 를 가리 키도록 만들어져
** 또는 [ temp_store_directory 프라 그마 ] 의 사용 은 피해야한다 .
**
** Windows 런타임 사용자 에 <B> 참고 : < / b > 임시 디렉터리를 설정 해야 합니다
** 전 [ sqlite3_open_v2 ] [ 에 sqlite3_open ] 호출 하기도한다. 그렇지 않으면 다양한
** 임시 파일 의 사용 을 필요로하는 기능이 실패 할 수 있습니다. 여기 에
** Windows 런타임 에서 C + +를 사용 하여 이렇게 방법을 보여줍니다.
**
** <BLOCKQUOTE> <PRE>
** LPCWSTR zPath = 의 Windows :: 스토리지 :: ApplicationData :: 전류 >
** TemporaryFolder - > 경로 - > 데이터 ( ) ;
** CHAR zPathBuf [ MAX_PATH + 1 ] ;
** memset 을 ( zPathBuf , 0, sizeof 연산 ( zPathBuf ) ) ;
** WideCharToMultiByte ( CP_UTF8 , 0, zPath , -1, zPathBuf 는 sizeof ( zPathBuf )
** NULL , NULL ) ;
** sqlite3_temp_directory = sqlite3_mprintf ( " % s " 는 zPathBuf ) ;
** < / PRE > < / BLOCKQUOTE >
* /
SQLITE_API SQLITE_EXTERN char *sqlite3_temp_directory;

/ *
** CAPI3REF : 이름 의 폴더 지주 데이터베이스 파일
**
** ^ ( 이 전역 변수 가 있는 문자열을 가리 키도록 이루어진 경우
** 폴더 의 ​​이름 ( 별명 디렉토리 ) 의 경우 모든 데이터베이스 파일
** 상대 경로명으로 지정 하여 작성 되었는지 에 의해 액세스되는
사용 하는 경우 ** SQLite 는 기본 제공 Windows [ sqlite3_vfs | VFS ] 는 간주됩니다
** 해당 디렉토리 에서 상대적인 . ) ^ ^ 이 변수 가 NULL의 경우
** 포인터 는 다음 SQLite 는 상정하고 , 그 지정된 모든 데이터베이스 파일
** 상대 경로 이름 커런트 디렉토리로부터 의 상대 경로 이다
** 프로세스 를 위해. VFS는 이 글로벌 을 이용하여 Windows 만
** 변수 , 그것은 , UNIX VFS 에 의해 무시 됩니다.
**
데이터베이스 연결 이있는 동안 ** 이 변수 의 값을 변경하려면
** 오픈 이 손상된 데이터베이스 가 될 수 있습니다.
**
** 이것은 여러 에서 이 변수를 읽거나 변경해도 안전 하지 않습니다
** 당시 스레드. 이것은 이 변수를 읽거나 변경해도 안전 하지 않습니다
** 데이터베이스 연결 은 별개로 동시에 사용 되는 경우
** 스레드 .
** 또한 이 변수가 한번 설정 되도록 설계 되어 있다
** 프로세스 초기화 의 일환으로 모든 SQLite 인터페이스 전에
** 루틴이 호출되고 ,이 변수는 변경 되지 않습니다 것을
** 다음 .
**
** ^ [ data_store_directory pragma는 이 변수와 원인을 해결 할 수있다
** 그것은 [ sqlite3_malloc ] 에서 가져온 메모리 를 가리 키도록 설정합니다. ^ 또한
** [ data_store_directory 프라 그마 ] 항상 전제 와 임의의 문자열
** 이 변수 포인트 는 메모리에 저장 되어 있는 것과는 여행
** [ sqlite3_malloc ] 및 pragma는 해당 메모리를 해제 하려고 시도 할 수있다
** [ sqlite3_free ] 사용.
이 변수가 직접 변경된 경우 ** 따라서 중 하나 이어야 합니다
** NULL을 하거나 , sqlite3_malloc ] 에서 가져온 메모리 를 가리 키도록 만들어져
** 또는 [ data_store_directory 프라 그마 ] 의 사용 은 피해야한다 .
* /
SQLITE_API SQLITE_EXTERN char *sqlite3_data_directory;

/ *
** CAPI3REF : 테스트 의 자동 위탁 모드
** KEYWORDS : { 커밋 모드 }
**
** ^ sqlite3_get_autocommit ( ) 인터페이스는 영이 아닌가 를 반환합니다.
** 제로 주어진 데이터베이스 연결 이 있는지 자동 커밋 모드로 되어 있지 않은 경우
** 각각. ^ 자동 커밋 모드 는 기본적으로 설정 되어 있습니다.
** ^ AutoCommit 모드는 BEGIN ] 문에서 사용할 수 있습니다.
** ^ AutoCommit 모드는 COMMIT 또는 ROLLBACK ] 다시 활성화 되고 있다.
**
** 오류는 특정 종류의 멀티 문 내에있는 명령문 에서 발생한 경우
** 트랜잭션 ( SQLITE_IOERR , SQLITE_FULL 을 포함 오류
** [ SQLITE_NOMEM , SQLITE_BUSY ] 및 [ SQLITE_INTERRUPT )를
** 트랜잭션 은 자동으로 롤백 될 수 있습니다. 의 유일한 방법
** SQLite 는 나중에 자동으로 트랜잭션을 롤백 여부 를 조사
** 오류는 이 기능을 사용 하는 것입니다.
**
** 다른 스레드 에는 데이터베이스 의 자동 확정 상태를 변경 한 경우
** 연결 이 루틴 을 실행하는 동안 반환
** 이 정의 되어 있지 않습니다.
* /
SQLITE_API int sqlite3_get_autocommit(sqlite3*);
/ * 
** CAPI3REF : 미리 컴파일 된 SQL 문을 데이터베이스 핸들을 찾을 
** 
** ^ sqlite3_db_handle 인터페이스는 데이터베이스 연결 핸들을 반환합니다 
** 상대의 준비된 문장]은 속합니다. ^ 데이터베이스 연결 
** 동일한 데이터베이스 연결을 sqlite3_db_handle에 의해 반환되는 
** 그것은 첫 번째 인수했다 
** [sqlite3_prepare_v2 () 호출 (또는 변형)을하는 데 사용되었다 
** 처음에 문을 만듭니다. 
* /
SQLITE_API sqlite3 *sqlite3_db_handle(sqlite3_stmt*);

/ * 
** CAPI3REF : 데이터베이스 연결 파일 이름을 반환합니다. 
** 
** ^ sqlite3_db_filename (D, N) 인터페이스는 파일 이름에 대한 포인터를 반환 
** 연결 D 데이터베이스 N ^ 메인 데이터베이스 파일에 연결된 
** '기본'이름이 붙어 있습니다. 데이터베이스에 연결된 데이터베이스 N이 존재하지 않는 경우 
** 연결 D 또는 데이터베이스 N이 다음 임시 또는 인 메모리 데이터베이스 인 경우 
** NULL 포인터가 반환됩니다. 
** 
** ^이 함수가 반환하는 파일 이름은 출력되는 
** [VFS]의 xFullPathname 방법. ^ 즉, 파일 이름 
** 파일 이름이 사용되고 있어도 절대 경로 이름입니다 
** 데이터베이스를 열려면 원래의 URI 또는 ​​상대 경로 이름이었다. 
* /
SQLITE_API const char *sqlite3_db_filename(sqlite3 *db, const char *zDbName);

/ * 
** CAPI3REF : 데이터베이스가 읽기 전용으로 결정합니다 
** 
** ^ sqlite3_db_readonly (D, N) 인터페이스 1을 반환하면 데이터베이스 N 
** 연결 D는 읽기 전용 0 / 쓰기 또는 -1을 읽고 있다면 N이 없을 경우에는 
** 연결 D.의 데이터베이스 이름 
* /
SQLITE_API int sqlite3_db_readonly(sqlite3 *db, const char *zDbName);

/ * 
** CAPI3REF : 다음 준비된 문장을 검색 
** 
** ^이 인터페이스는 나중에 다음 [준비된 문]에 대한 포인터를 반환 
**는 pstmt 데이터베이스 연결 PDB에 연결된. ^ 만약 다시 호출은 NULL입니다 
**이 인터페이스는 먼저 준비된 문장에 대한 포인터를 반환 
** 데이터베이스 연결 PDB에 연결된. ^ NO의 경우 준비된 문 응 
**이 루틴의 조건을 충족하는 경우 NULL을 반환합니다. 
** 
** 데이터베이스 연결 호출 포인터 D 
** [sqlite3_next_stmt (D, S)]가 열려있는 데이터베이스를 참조해야합니다 
** 연결, 특히 NULL 포인터 여서는 안됩니다. 
* /
SQLITE_API sqlite3_stmt *sqlite3_next_stmt(sqlite3 *pDb, sqlite3_stmt *pStmt);

/ *
** CAPI3REF : 커밋 알림 콜백을 롤백
**
** ^ sqlite3_commit_hook ( ) 인터페이스는 콜백 등록
[ | 커밋 COMMIT 트랜잭션 이있을 때는 언제든지 ** 함수 가 호출된다.
** ^ 이전 호출에 의해 설정된 콜백이 sqlite3_commit_hook ( ) 의
** 동일한 데이터베이스 연결 을 재정의 했기 때문이다.
** ^ sqlite3_rollback_hook ( ) 인터페이스는 콜백 등록
** 함수는 트랜잭션이 있을 때 마다 불려 [ ROLLBACK | 롤백 .
** ^ 이전 호출에 의해 설정된 콜백이 sqlite3_rollback_hook ( ) 의
** 동일한 데이터베이스 연결 을 재정의 했기 때문이다.
** ^ PARG 인수는 콜백 에 전달됩니다.
** ^ 커밋 후크 콜백이 0이 아닌 반환하는 경우
** 다음 커밋, 롤백 으로 변환 됩니다.
**
** ^ sqlite3_commit_hook ( D , C , P ) 과 sqlite3_rollback_hook ( D , C , P ) 의 함수
** 동일한 함수 의 이전 호출 에서 P 인수를 반환
** 동일한 데이터베이스 연결 의 연구 개발 또는 NULL 을위한
** D 의 각 함수 의 최초의 호출
**
** 커밋 및 롤백 후크 콜백은 재진입 없습니다.
** 콜백 구현이 변경 됩니다 아무것도 안됩니다
** 콜백 을 호출 한 데이터베이스 연결 . 모든 작업
** 데이터베이스 연결을 변경하려면 후 까지 연기 되어야 한다
** 커밋 을 일으킨 [ sqlite3_step ( ) 호출 완료
** 또는 원래 롤백 후크 .
** 그것이 SELECT 문을 포함하여 다른 SQL 문을 실행 주의 하십시오
** 아니면 그냥 호출 [ sqlite3_prepare_v2 을 ( ) 및 sqlite3_step ( ) 로 변경 합니다
** 이 단락 에서 " 변경 " 의 의미에 대해서는 데이터베이스 연결 .
**
** ^ NULL 기능을 등록 하면 콜백 을 비활성화 합니다.
**
** ^ commit 후크 콜백 루틴 은 0 을 반환하면 , COMMIT ]
** 동작은 정상적으로 계속 한다. ^ 후크 를 커밋 한 경우
** 비 제로를 돌려 다음 COMMIT ] 는 [ ROLLBACK ] 로 변환 한다.
** ^ 롤백 훅 은 커밋 한 결과, 롤백 로 불려
** 그것은 다른 롤백 과 함께 하는 것과 마찬가지로 0 이 아닌 값을 반환 후크 .
**
** ^ 이 API 의 목적을 위해 트랜잭션 이 있었다고 전해지고 있습니다
** 명시 적 " 롤백 " 문장 이 실행 된 경우 , 롤백 또는
** 오류 또는 제약 이 생겨 암시 적 롤백 이 발생합니다.
트랜잭션이있는 경우 ** ^ 롤백 콜백이 호출 되지 않는다
데이터베이스 연결 이 닫혀 있기 때문에 ** 자동으로 롤백 .
**
** 도 [ sqlite3_update_hook ( ) 인터페이스를 참조 하십시오.
* /
SQLITE_API void *sqlite3_commit_hook(sqlite3*, int(*)(void*), void*);
SQLITE_API void *sqlite3_rollback_hook(sqlite3*, void(*)(void *), void*);

/ *
** CAPI3REF : 데이터 변경 알림 콜백
**
** ^ sqlite3_update_hook ( ) 인터페이스는 콜백 함수를 등록합니다
** 에게 첫 번째 인수 로 식별되는 데이터베이스 연결
행이 갱신 , 삽입 또는 제거 될 때 호출된다. **
** ROWID 테이블.
** ^ 이 함수 의 이전 호출에 의해 설정된 콜백
** 동일한 데이터베이스 연결 을 재정의 했기 때문이다.
**
** ^ 두 번째 인수는 호출하는 함수 에 대한 포인터 일 때
** 행은 업데이트, 삽입 또는 ROWID 테이블 에 삭제 됩니다.
** ^ 콜백 의 첫 번째 인수는 세 번째 인수 의 복사본입니다
** ( sqlite3_update_hook 위하여).
** ^ 두 번째 콜백 인수는 SQLITE_DELETE , SQLITE_INSERT ] 의 하나이며,
** 또는 SQLITE_UPDATE , 작업에 따라 콜백 을 일으킨
** 호출된다.
** ^ 콜백 의 세 번째 및 네 번째 인수는 포인터 가 포함 된
** 데이터베이스 및 영향을 받는 행 을 포함하는 테이블 이름 .
** ^ 마지막 콜백 매개 변수는 ROWID 줄 것입니다.
** ^ 업데이트 의 경우 이것은 업데이트 가 이루어 【 행 ID ] 뒤에 있다.
**
내부 시스템 테이블 이있는 경우 ** ^ ( update 훅은 시작 되지 않습니다
** 수정 된 ( 즉 SQLITE_MASTER 과 sqlite_sequence ) . ) ^
없음 ROWID ] 테이블이 변경된 경우 ** ^ update 훅은 시작 되지 않습니다 .
**
** ^ 현재 구현 에서는 update 훅
중복 행이 제거 된 때 ** 로 인해 시작 되지 않습니다
** | 어구를 [ 분쟁에 관한 분쟁에 관한 REPLACE ] . ^ NOR update 훅입니다
줄이 TRUNCATE 최적화 를 사용하여 제거 될 때 호출된다. **
** 이 단락 에서 정의 된 예외는 향후 변경 될 수 있습니다
** SQLite는 릴리스 .
**
** update 훅 의 구현이 변경 됩니다 아무것도 안됩니다
** update 훅을 시작 하여 데이터베이스 연결 . 모든 작업
** 데이터베이스 연결을 변경하려면 후 까지 연기 되어야 한다
** update 훅을 일으킨 [ sqlite3_step ( ) 호출 완료.
** [ sqlite3_prepare_v2 ( ) 및 sqlite3_step 은 ( ) 변경 모두 가 그
** 데이터베이스 이 단락 에서 " 변경 " 의 의미 에 대한 연결 .
**
** ^ sqlite3_update_hook ( D , C , P ) 함수
** 이전 호출 에서 P 인수를 반환
** 동일한 데이터베이스 연결 의 연구 개발 또는 NULL 을위한
** D 의 첫 번째 호출
**
** [ ) sqlite3_rollback_hook ( ] 도 [ sqlite3_commit_hook ( ) 과 를 참조 하십시오.
** 인터페이스.
* /
SQLITE_API void *sqlite3_update_hook(
  sqlite3*, 
  void(*)(void *,int ,char const *,char const *,sqlite3_int64),
  void*
);

/ *
** CAPI3REF 해제하거나 공유 호출기 캐시
**
** ^ ( 이 루틴은 데이터베이스 캐시 의 공유 를 활성화 또는 비활성화 합니다
사이 ** 및 스키마 데이터 구조 데이터베이스 연결 | 연결
** 동일한 데이터베이스에 . 인수가 true 의 경우 공유 가 활성화되어 있는
인수가 false 의 경우 ** 및 사용할 수 있습니다. ) ^
**
** ^ 캐시 공유가 활성화 되어있어 전체 프로세스 에 사용할 수 있습니다.
** 이것은 SQLite 버전 3.5.0 과 같은 변화 이다. SQLite 의 이전 버전 에서는
** 공유 를 활성화 하거나 별도로 각 스레드 에 사용할 수 있었습니다.
**
이후 의 모든 이 인터페이스 의 영향 에 의해 설정된 ** ^ ( 캐시 공유 모드
** [에서 sqlite3_open ( ) , sqlite3_open_v2 ( ) ] 및 [ sqlite3_open16 ( ) 를 호출합니다.
** 기존 데이터베이스 연결 은 공유 모드 를 사용하여 계속
** 그들이 열린 시점에서 유효 했다. ) ^
**
** ^ ( 이 루틴은 [ SQLITE_OK ] 공유 캐시 를 활성화 또는 비활성화 한 경우에는
** 성공. [ 오류 코드 ] 가 그렇고 반환됩니다. ) ^
**
** ^ 공유 캐시는 기본적으로 비활성화되어 있습니다. 그러나 이것은 변경 될 수 있습니다
SQLite 의 ** 릴리스 . 공유 를 꺼린다 응용 프로그램
** 캐시 설정을 명시 적으로 설정 해야 합니다.
**
쓰기 위치 ** 이 인터페이스는 프로세서에서 스레드로부터 안전 이다
** 32 비트 정수는 원자 입니다.
**
** 참고 항목 : SQLite 의 공유 캐시 모드 ]
* /
SQLITE_API int sqlite3_enable_shared_cache(int);

/ * 
** CAPI3REF : 무료 힙 메모리를 시도 
** 
** ^ sqlite3_release_memory는 () 인터페이스는 N 바이트를 해제하려고 
** 힙 메모리의 비 필수 메모리 할당의 할당을 해제함으로써 
** 데이터베이스 라이브러리가 보유하고있다. 캐시 데이터베이스에 사용되는 메모리 
** 성능을 향상시키기 위해 페이지는 비 본질적인 메모리의 일례이다. 
** ^ sqlite3_release_memory ()는 실제로 해제 된 바이트 수를 반환합니다 
** 이상 또는 요구 된 양보다 적을지도 모른다. 
** ^ sqlite3_release_memory () 루틴은 0을 반환하고 아무것도하지 않습니다 
** SQLite는 [SQLITE_ENABLE_MEMORY_MANAGEMENT을 사용하여 컴파일되지 않은 경우. 
** 
** 참조 : [sqlite3_db_release_memory을 () 
* /
SQLITE_API int sqlite3_release_memory(int);

/ * 
** CAPI3REF : 데이터베이스 연결에 사용 가능한 메모리 
** 
** ^ 많은 힙을 해제하는 sqlite3_db_release_memory (D) 인터페이스의 시도 
**과 달리 데이터베이스 연결 D에서 가능한 메모리 
** [sqlite3_release_memory () 인터페이스는이 인터페이스가 활성화되어 있어도 
** 때 [SQLITE_ENABLE_MEMORY_MANAGEMENT] 컴파일시의 옵션이있다 
** 생략. 
** 
** 참조 : [sqlite3_release_memory을 () 
* /
SQLITE_API int sqlite3_db_release_memory(sqlite3*);

/ *
** CAPI3REF : 힙 크기 제한 을 부과
**
** ^ sqlite3_soft_heap_limit64 ( ) 인터페이스 세트 및 / 또는 문의
SQLite 때문에 할당 할 수있는 힙 메모리 의 양 에 ** 약한 제한 .
** ^ SQLite 는 소프트 힙 아래에 힙 메모리 사용률 을 유지하기 위해 노력하고 있습니다
** 페이지 캐시에 보관 된 페이지 수를 줄임으로써 제한
** 힙 메모리 사용량 등 의 한계 에 접근한다.
SQLite 는 있어야 노력 하고 있었다고해도 아직은 ** ^ 소프트 힙 한계 는 '소프트' 이다
** 한도 이하로 는 제한을 초과하는 것이 아니라 생성 됩니다
** [ SQLITE_NOMEM ] 오류가 발생 했습니다. 즉, 소프트 힙 한계
** 유일한 지도자이다.
**
** ^ sqlite3_soft_heap_limit64 의 반환 값 은 ( ) 의 크기
** 소프트 힙 호출하기 전에 제한하거나 예 부정적인
** 오류 . ^ 인수 N 가 부의 경우
** 다음 변화가 소프트 힙 제한 되지 않습니다. 따라서 현재
** 소프트 힙 한계 크기를 호출하여 결정할 수 있다
음수 인수로 ** sqlite3_soft_heap_limit64 ( ) .
**
인수 n가 제로 의 경우 ** ^ 소프트 힙 한계 가 비활성화되어 있습니다.
**
** ^ ( 소프트 힙 한계는 현재 의 구현에서는 강제 되지 않습니다
** 다음 조건 중 하나 이상 에 해당하는 경우 :
**
** <UL>
** 소프트 힙 한계 가 제로로 설정 되는 <LI> .
** <LI> 메모리 회계 는 조합을 사용하여 사용할 수 있습니다
** [ sqlite3_config ] ( SQLITE_CONFIG_MEMSTATUS , ... ) 를 시작할 때 옵션 과
** [ SQLITE_DEFAULT_MEMSTATUS ] 컴파일 시 옵션 .
** <LI> 대체 페이지 캐시 의 구현은 사용하여 지정 되는
** [ sqlite3_config ] ( SQLITE_CONFIG_PCACHE2 , ... ) .
** <LI> 페이지 캐시는 지정된 이는 메모리 풀 에서 할당
** ( SQLITE_CONFIG_PAGECACHE , ... ) [ sqlite3_config 대신 ,
** 힙 에서 .
** < / UL > ) ^
**
** SQLite 버전 3.7.3 이상에서는 소프트 힙 제한이 적용됩니다
** 여부에 관계없이 [ SQLITE_ENABLE_MEMORY_MANAGEMENT ] 의
** 컴파일 시 의 옵션이 호출됩니다. [ SQLITE_ENABLE_MEMORY_MANAGEMENT ] 와
** 소프트 힙 한계는 모든 메모리 할당 에 적용 됩니다. 없음
** [ SQLITE_ENABLE_MEMORY_MANAGEMENT 소프트 힙 한계 에만 적용 됩니다
** 메모리 가 페이지 캐시 에서 할당 한 때. 테스트 제안 하고 있기 때문에 ,
** 페이지 캐시 는 SQLite 에서 지배적 인 메모리 의 사용자 는 대부분의
** 응용 프로그램 이 없어도 충분한 소프트 힙 제한 의 적용을 달성하기
** [ SQLITE_ENABLE_MEMORY_MANAGEMENT 을 사용 한다.
**
** SQLite 가 소프트 힙 제한을 강제 되는 상황 달
** SQLite는 릴리스 에서는 변경 됩니다.
* /
SQLITE_API sqlite3_int64 sqlite3_soft_heap_limit64(sqlite3_int64 N);

/ * 
** CAPI3REF : 비추천 소프트 힙 제한 인터페이스 
** 비추천 
** 
**이되지 않는 버전입니다 [sqlite3_soft_heap_limit64 () 
** 인터페이스. 이 루틴은 역사적인 호환성을 위해 제공되는 
** 만. 모든 새로운 응용 프로그램은 사용해야합니다 
** [sqlite3_soft_heap_limit64 () 인터페이스가 아닌이 1. 
* /
SQLITE_API SQLITE_DEPRECATED void sqlite3_soft_heap_limit(int N);

/ *
** CAPI3REF : 테이블의 열에 관한 메타 데이터 추출
**
** ^ 특정 특정 열에 대한 이 루틴은 메타 데이터
데이터베이스 연결을 취급 사용하여 ** 데이터베이스 테이블 에 액세스 가능
** 첫 번째 함수 의 인수로 전달 되었다.
**
** ^ 열이 제 2, 제 3, 제 4 매개 변수로 식별 된
** 이 기능 . ^ 두 번째 매개 변수는 데이터베이스 의 이름 중 하나 인
** (즉, "주 ", " TEMP " 또는 연결된 데이터베이스 ) 를 포함 지정된
** 테이블 또는 NULL . 그것이 NULL의 경우 ^ 은 연결되어 있는 모든 데이터베이스 가 검색 됩니다
** 테이블 의 데이터베이스 엔진 에 사용되는 것과 같은 알고리즘을 사용하여
** 해결 되지 않은 테이블 참조 .
**
** ^ 이 함수 의 세 번째와 네 번째 매개 변수는 테이블 과 열 이다
** 각각 원하는 열의 이름입니다. 이러한 매개 변수를 모두
** NULL 이 될 수 있습니다.
**
** ^ 메타 데이터 는 다섯 번째 로 전달 된 메모리 위치 에 작성하여 반환
이 함수 ** 파라미터 이상 . ^ 이 인수 할 수있다
** 메타 데이터 의 해당 요소 를 생략 한 경우에는 NULL입니다.
**
** ^ ( <BLOCKQUOTE>
** <table border="1">
** <TR> 번째 매개 변수 번째 출력 의 설명을 입력 번째 관
**
** <TR> <TD> 다섯째 const char * 문자 <TD> 데이터 형식 <TD>
** 는 const char 형 <TD> <TR> <TD> 여섯째 * 기본 데이터 정렬 <TD> 이름
** <TR> <TD> 일곱째 <TD> INT <TD> 진정한 열은 NOT NULL 제약 조건 이있는 경우
** <TR> <TD> 여덟째 <TD> INT <TD> 진정한 열은 기본 키 의 일부인 경우
** <TR> <TD> 아홉째 <TD> INT <TD> 트루 열이 자동 증가 값 의 경우
** < / 테이블 >
** < / BLOCKQUOTE > ) ^
**
** ^ 문자 포인터 가 가리키는 메모리를 위해 리턴
** 선언 의 형식과 데이터 정렬은 다음 까지 유효합니다
** 모든 SQLite API 함수 를 호출합니다.
**
지정된 테이블은 실제로 뷰 의 경우 ** ^ [ 오류 코드 를 반환합니다.
**
** ^ 지정된 열이 " ROWID " 의 경우 " OID "또는 " _ROWID_ "고
** 정수 PRIMARY KEY 열은 명시 적으로 출력 하여 선언 되어 있습니다
** 매개 변수를 명시 적으로 선언 된 라인으로 설정 되어 있다. ^ ( 전혀 존재 하지 않는 경우
** 명시 적으로 선언 정수 PRIMARY KEY 열 출력
다음과 같이 ** 매개 변수 가 설정되어 있습니다.
**
** <PRE>
** 데이터 형식 : " 정수 "
** 조합 순서 : " 이진 "
** NOT NULL : 0
** PK : 1
** 자동 증가 : 0
** < / pre > 의 ) ^
**
** ^ ( 이 기능은 데이터베이스 파일 에서 하나 이상의 스키마를 로드 할 수 있는 경우
** 오류는이 과정 동안에 발생한 경우, 또는 요구 된 테이블 또는 열
** 찾을 수 없습니다 오류 코드 ] 반환되고 오류 메시지가 남아
** 데이터베이스 연결 에서 ( ) ( sqlite3_errmsg 를 사용하여 검색 된다). ) ^
**
라이브러리를 컴파일 한 경우 ** ^ 이 API는 제공 되고 있습니다
** [ SQLITE_ENABLE_COLUMN_METADATA C - 전 처리기 기호 가 정의 되어 있다.
* /
SQLITE_API int sqlite3_table_column_metadata(
  sqlite3 *db,                /* Connection handle */
  const char *zDbName,        /* Database name or NULL */
  const char *zTableName,     /* Table name */
  const char *zColumnName,    /* Column name */
  char const **pzDataType,    /* OUTPUT: Declared data type */
  char const **pzCollSeq,     /* OUTPUT: Collation sequence name */
  int *pNotNull,              /* OUTPUT: True if NOT NULL constraint exists */
  int *pPrimaryKey,           /* OUTPUT: True if column part of PK */
  int *pAutoinc               /* OUTPUT: True if column is auto-increment */
);

/ *
** CAPI3REF : 확장을 적재
**
** ^ 이 인터페이스는 지정된 파일에서 SQLite 확장 라이브러리를로드 합니다.
**
** ^ sqlite3_load_extension 는 ( ) 인터페이스는 로드하려고 합니다
파일 zFile 에 포함 된 ** [ SQLite 확장 라이브러리 . 만약
** 파일 은 직접 시도가 로드 하기 위해 수행 되는 로드 할 수 없습니다
** 다양한 운영 체제 고유 의 확장 기능을 추가했다.
** 따라서 예를 들어, " samplelib " 를로드 할 수 없는 경우에는 이름 과 같은
** " samplelib.so "또는 " samplelib.dylib "또는 " samplelib.dll " 마이트
** 도 시도 된다.
**
** ^ 엔트리 포인트 zProc 입니다.
** ^ ( zProc 는 SQLite 가 마련하려 하고 그 경우 0 이다
** 독자적으로 엔트리 포인트 이름 . 이것은 첫 번째 " sqlite3_extension_init " 을 하려고 합니다.
그래도 문제가 해결 되지 않으면 ** 이름 " sqlite3_X_init " 를 작성하는 경우
** X는 모든 ASCII 알파벳 소문자 상응 로 구성되어 있습니다
** 먼저 다음 의 마지막 " / " 에서 파일 이름 의 문자
** " " 모든 첫 번째 " LIB " 를 생략했다. ) ^
** ^ sqlite3_load_extension ( ) 인터페이스 로 돌아갑니다
** [ SQLITE_OK ] 성공 하고 SQLITE_ERROR ] 뭔가 잘못되면 .
** ^ 오류가 발생 하고 pzErrMsg 그때 0이 아닌 경우
** [ sqlite3_load_extension ( ) 인터페이스는 시도 해야한다
메모리에 저장 되는 오류 메시지 텍스트 에서 ** 채우기 * 의 pzErrMsg
** [ sqlite3_malloc ( ) ] 에서 입수했다. 함수 호출
** 호출 이 메모리를 해제 해야 합니다 [ sqlite3_free 을 ( ) .
**
** ^ 확장 부하 사용하여 활성화 해야 합니다
** [ sqlite3_enable_load_extension ( ) 종래 , 이 API 를 호출하는
** 그렇지 않으면 오류가 반환됩니다.
**
** 도 [ load_extension ( ) SQL 함수 를 참조 하십시오.
* /
SQLITE_API int sqlite3_load_extension(
  sqlite3 *db,          /* Load the extension into this database connection */
  const char *zFile,    /* Name of the shared library containing extension */
  const char *zProc,    /* Entry point.  Derived from zFile if 0 */
  char **pzErrMsg       /* Put error message here if not 0 */
);

/ * 
** CAPI3REF 해제하거나 확장 모듈로드 
** 
오래된 응용 프로그램에서 ** ^ 같이 열리지 않는 보안 구멍 
** 고급 가져 오기에 대처할 준비가되어 있지 않으며, 해제하는 수단으로 
** 고급로드] 사용자가 입력 한 SQL을 평가하면서 다음 API 
**는 온과 오프 메커니즘 [() sqlite3_load_extension을 선택하기 위해 설치되어있다. 
** 
** ^ 확장로드는 기본적으로 꺼져 있습니다. 
ONOFF에서 ** ^ sqlite3_enable_load_extension ()를 호출 루틴 == 1 
**의 확장로드를 선택하고 선택 ONOFF == 0에서 호출 
** 다시 백 오프. 
* /
SQLITE_API int sqlite3_enable_load_extension(sqlite3 *db, int onoff);

/ *
** CAPI3REF : 자동으로 정적으로 링크 된 확장 기능을 로드합니다.
**
** ^ 이 인터페이스는 xEntryPoint ( ) 함수 에 대한 호출됩니다
** 각각 의 새 데이터베이스 연결 던데 생성 됩니다. 여기 에서 아이디어는
** xEntryPoint ( ) 는 정적으로 링크 된 [ SQLite 확장 모듈 의 진입 점 이다
** 그것은 자동으로 모든 새 데이터베이스 연결 에 로드 하는 것입니다.
**
** ^ ( 함수 프로토 타입은 xEntryPoint ( ) 이 부과 것으로 나타 있는데,
** 인수와 반환 무효 , SQLite 는 ( ) 3 xEntryPoint 를 호출
** 인수 것으로 예상하고 정수 결과 것처럼 서명
** 진입 점은 다음 과 같다 :
**
** <BLOCKQUOTE> <PRE>
** int 형 xEntryPoint (
** 의 sqlite3 * dB,
** 는 const char 형 ** pzErrMsg ,
** const 구조체 의 sqlite3_api_routines * pThunk
** ) ;
** < / PRE > < / BLOCKQUOTE > ) ^
**
xEntryPoint 루틴 에서 오류가 발생하면 ** 는 * 의 pzErrMsg 을 해야 한다
** 적절한 오류 메시지 포인트 ( 에서 입수 한 [ sqlite3_mprintf ( ) ] )
** 적절한 오류 코드 를 반환합니다. ^ SQLite 는 확실히 그 * pzErrMsg
** xEntryPoint ( ) 를 호출하기 전에 NULL입니다 . ^ SQLite 는 시작합니다
** [ sqlite3_free ( ) ] * pzErrMsg 에 xEntryPoint 후 ( ) 가 반환 . ^ 있는 경우
** xEntryPoint ( ) 가 오류를 반환 [로 sqlite3_open ( ) , sqlite3_open16 ( ) ,
xEntryPoint 을 일으키는 ** 또는 [ sqlite3_open_v2 ( ) ( ) 의 호출 에 실패합니다.
**
** ^ 이미 진입 점 X 에 sqlite3_auto_extension ( X ) 를 호출
** 자동 확장 기능 목록 에 무해한 무 조작 입니다. ^ 진입 점 없음
** 보다 열린 각 데이터베이스 연결 을위한 여러 번 이라고합니다.
**
** 참조 : [ sqlite3_reset_auto_extension 을 ( )
** 및 sqlite3_cancel_auto_extension ( )
* /
SQLITE_API int sqlite3_auto_extension(void (*xEntryPoint)(void));

/ * 
** CAPI3REF : 자동 연장 취소로드 중 
** 
** ^ [sqlite3_cancel_auto_extension (X) 인터페이스는 등록 취소 
호출 전에를 사용하여 등록 된 ** 초기화 루틴 X 
** [sqlite3_auto_extension (X). ^ [sqlite3_cancel_auto_extension (X) 
초기화 루틴 X가 성공했는지 ** ​​리턴 1 
** 등록 취소 및 X 초기화 목록에 실려 있지 않은 경우는 0을 돌려줍니다. 
** 일과. 
* /
SQLITE_API int sqlite3_cancel_auto_extension(void (*xEntryPoint)(void));
/ * 
** CAPI3REF : 자동 확장 모듈로드를 재설정 
** 
** ^이 인터페이스는 이전에 모든 자동 증가를 해제합니다 
** 사용하여 등록 [sqlite3_auto_extension을 (). 
* /
SQLITE_API void sqlite3_reset_auto_extension(void);
/ * 
** 가상 테이블기구의 인터페이스는 현재 간주됩니다 
** 실험적이라고. 인터페이스는 호환되지 않는 방식으로 변경 될 수 있습니다. 
** 이것은 당신을위한 문제이면이 시점에서는 인터페이스를 사용하지 마십시오. 
** 
** 가상 테이블기구가 안정되면, 우리는 선언합니다 
** 인터페이스는 고정 무기한 그것을 지원하고이 댓글을 삭제하십시오. 
* /

/*
** Structures used by the virtual table interface
*/
typedef struct sqlite3_vtab sqlite3_vtab;
typedef struct sqlite3_index_info sqlite3_index_info;
typedef struct sqlite3_vtab_cursor sqlite3_vtab_cursor;
typedef struct sqlite3_module sqlite3_module;

/ * 
** CAPI3REF : 가상 테이블 개체 
** KEYWORDS : sqlite3_module {가상 테이블 모듈} 
** 
**이 구조는 종종 "가상 테이블 모듈"라는 
** 가상 테이블의 구현을 정의합니다. 
**이 구조는 모듈을위한 방법의 대부분이 구성되어 있습니다. 
** 
** ^ 가상 테이블 모듈은 영구적를 매장해서 만들어지는 
**이 구조체의 인스턴스와 해당 인스턴스에 대한 포인터를 전달 
**에 [sqlite3_create_module () 또는 sqlite3_create_module_v2 (). 
그것은 다른 곳으로 옮겨까지 ** ^ 등록은 유효한 상태 
** 모듈 또는 데이터베이스 연결은 닫을 때까지. 콘텐츠 
그것은에 등록되어있는 동안 **이 구조의 변화는 안된다 
** 모든 데이터베이스 연결. 
* /
struct sqlite3_module {
  int iVersion;
  int (*xCreate)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xConnect)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xBestIndex)(sqlite3_vtab *pVTab, sqlite3_index_info*);
  int (*xDisconnect)(sqlite3_vtab *pVTab);
  int (*xDestroy)(sqlite3_vtab *pVTab);
  int (*xOpen)(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor);
  int (*xClose)(sqlite3_vtab_cursor*);
  int (*xFilter)(sqlite3_vtab_cursor*, int idxNum, const char *idxStr,
                int argc, sqlite3_value **argv);
  int (*xNext)(sqlite3_vtab_cursor*);
  int (*xEof)(sqlite3_vtab_cursor*);
  int (*xColumn)(sqlite3_vtab_cursor*, sqlite3_context*, int);
  int (*xRowid)(sqlite3_vtab_cursor*, sqlite3_int64 *pRowid);
  int (*xUpdate)(sqlite3_vtab *, int, sqlite3_value **, sqlite3_int64 *);
  int (*xBegin)(sqlite3_vtab *pVTab);
  int (*xSync)(sqlite3_vtab *pVTab);
  int (*xCommit)(sqlite3_vtab *pVTab);
  int (*xRollback)(sqlite3_vtab *pVTab);
  int (*xFindFunction)(sqlite3_vtab *pVtab, int nArg, const char *zName,
                       void (**pxFunc)(sqlite3_context*,int,sqlite3_value**),
                       void **ppArg);
  int (*xRename)(sqlite3_vtab *pVtab, const char *zNew);
  /* The methods above are in version 1 of the sqlite_module object. Those 
  ** below are for version 2 and greater. */
  int (*xSavepoint)(sqlite3_vtab *pVTab, int);
  int (*xRelease)(sqlite3_vtab *pVTab, int);
  int (*xRollbackTo)(sqlite3_vtab *pVTab, int);
};

/ *
** CAPI3REF : 가상 테이블 의 인덱스 정보
** KEYWORDS : sqlite3_index_info
**
** sqlite3_index_info 구조 및 기초 구조를 일부로 사용됩니다
** 가상 테이블 인터페이스 에
** 로 정보를 전달 , xBestIndex ] 에서 응답 을 수신
** 가상 테이블 모듈 방법 . ** 입력 아래 의 필드 ** 는
** 입력 xBestIndex 그러면 읽기 전용입니다. xBestIndex 가 삽입됩니다 그
** 출력 ** 필드 에 결과 .
**
** ^ ( aConstraint [] 배열 레코드 의 WHERE 절 형식 의 제한 :
**
** <BLOCKQUOTE> 란 OP expr 을 < / BLOCKQUOTE >
**
** OP 가 = , <, < =,> 또는 > = ) ^ 은 ^ ( 특히 연산자
중 하나를 사용하여 ** aConstraint 에 저장되고 [] . OP
** [ SQLITE_INDEX_CONSTRAINT_EQ | SQLITE_INDEX_CONSTRAINT_ 값 ) ^
** ^ ( 열의 인덱스는 저장 되어있는
** aConstraint [] . iColumn . ) ^ ^ 는 ( aConstraint [] . 사용할 수있는 참이면
** 오른쪽 expr 에는 이러한 제약 을 평가 ( 수
** 사용 가능 ) 에 동의 할 수없는 경우 는 false입니다. ) ^
**
** ^ 최적화 프로그램은 자동으로 양식 " expr 은 OP 란 " 조항을 반전
** 는 시도 는 WHERE 절 에 다른 단순화 할
** 최대한 위와 같은 형식으로 많은 WHERE 절 조건 을 얻는다.
** ^ aConstraint [] 배열 에만 보고 WHERE 절 이다 조건
** 특정 가상 테이블 에 관련 이 조회 되고 있다.
**
** ^ ORDER BY 절 에 대한 정보는 [] aOrderBy 에 저장 되어 있다.
** ^ aOrderBy 절 은 ORDER BY 절의 열 을 기록합니다.
**
** [ xBestIndex ] 이 방법은 정보를 [] aConstraintUsage 를 입력 해야 합니다
** xFilter 에 전달 을 매개 변수 . ^ 만약 argvIndex > 0 그리고
** 해당 aConstraint 의 오른쪽 [] 는 정격
** 및 argv 내 argvIndex 번째 항목 입니다. ^ ( aConstraintUsage [] 합니다. 생략
** 제약 조건이 완전히 의해 처리 되는 것과 사실입니다
** 가상 테이블은 SQLite 에 의해 다시 확인하지 않습니다. ) ^
**
** ^ idxNum 과 idxPtr 값을 기록 하고 에 전달
** [ xFilter ] 의 방법 .
** ^ [ sqlite3_free ( ) ] idxPtr 를 해제 하는 데 사용 되는 경우에만
** needToFreeIdxPtr 사실이다.
**
** ^ orderByConsumed 는 [ xFilter ] / [ xNext 에서 이루어 지기 때문에 출력을 의미
** ORDER BY 절을 충족 올바른 순서 가되도록 개별 없음
** 선별 공정이 필요하다.
**
** ^ estimatedCost 값은 특정 비용 의 추정치 이다
** 전략 . N 의 비용은 전략 의 비용 이 유사하고 있다는 것을 보여준다
** N 행 과 SQLite 테이블 의 선형 주사한다. 로그 의 비용 ( N )
** 작업 비용이 의 것과 동일 하다는 것을 보여
** N 행 과 SQLite 테이블 의 고유 인덱스 필드 의 이진 검색 .
**
** ^ estimatedRows 값은 행 수 의 예측 이다
** 전략 에 의해 반환됩니다.
**
** 중요 : estimatedRows 필드를 sqlite3_index_info 에 추가 되었습니다
** SQLite 버전 3.8.2 에 대한 구조. 가상 테이블 의 확장 이있는 경우
** 3.8.2 이전 SQLite 버전 에서 사용 하려고 한 결과
** estimatedRows 필드 를 읽고 쓰는 정의 되지 않습니다 ( 그러나 가능성
** 응용 프로그램 ) 충돌 포함됩니다. estimatedRows 필드 이어야
[ sqlite3_libversion_number 는 ( )가 반환 된 경우 ** 따라서 만 사용하여
** 값 보다 큰지 3008002 같다.
* /
struct sqlite3_index_info {
  /* Inputs */
  int nConstraint;           /* Number of entries in aConstraint */
  struct sqlite3_index_constraint {
     int iColumn;              /* Column on left-hand side of constraint */
     unsigned char op;         /* Constraint operator */
     unsigned char usable;     /* True if this constraint is usable */
     int iTermOffset;          /* Used internally - xBestIndex should ignore */
  } *aConstraint;            /* Table of WHERE clause constraints */
  int nOrderBy;              /* Number of terms in the ORDER BY clause */
  struct sqlite3_index_orderby {
     int iColumn;              /* Column number */
     unsigned char desc;       /* True for DESC.  False for ASC. */
  } *aOrderBy;               /* The ORDER BY clause */
  /* Outputs */
  struct sqlite3_index_constraint_usage {
    int argvIndex;           /* if >0, constraint is part of argv to xFilter */
    unsigned char omit;      /* Do not code a test for this constraint */
  } *aConstraintUsage;
  int idxNum;                /* Number used to identify the index */
  char *idxStr;              /* String, possibly obtained from sqlite3_malloc */
  int needToFreeIdxStr;      /* Free idxStr using sqlite3_free() if true */
  int orderByConsumed;       /* True if output is already ordered */
  double estimatedCost;           /* Estimated cost of using this index */
  /* Fields below are only available in SQLite 3.8.2 and later */
  sqlite3_int64 estimatedRows;    /* Estimated number of rows returned */
};

/ * 
** CAPI3REF : 가상 테이블 제약 운영자 코드 
** 
**이 매크로는 사용할 수있는 값을 정의한 
** [sqlite3_index_info]. aConstraint []. OP 필드. 각 값은 나타 
** WHERE 절 제한 기간의 일부이며 운영자 
** 가상 테이블을 사용하는 쿼리입니다. 
* /
#define SQLITE_INDEX_CONSTRAINT_EQ    2
#define SQLITE_INDEX_CONSTRAINT_GT    4
#define SQLITE_INDEX_CONSTRAINT_LE    8
#define SQLITE_INDEX_CONSTRAINT_LT    16
#define SQLITE_INDEX_CONSTRAINT_GE    32
#define SQLITE_INDEX_CONSTRAINT_MATCH 64

/ *
** CAPI3REF : 가상 테이블 의 구현을 등록
**
** ^ 이러한 루틴은 새로운 가상 테이블 모듈 이름을 등록 하는 데 사용 됩니다.
** ^ 모듈 이름은 전에 등록 해야 합니다
** NEW 가상 테이블을 만드는 모듈 을 사용하여 사용 하기 전에
** 모듈 의 가상 테이블을 기존.
**
** ^ 모듈 이름이 데이터베이스 연결 에 등록 된 지정된
** 첫 번째 매개 변수 . ^ 모듈 의 이름은 다음 식으로 주어진다.
** 번째 매개 변수입니다. ^ 세 번째 매개 변수는 몸 에 대한 포인터입니다
** 가상 테이블 모듈 의 구현 . ^ 중
** 매개 변수가 통하는 모든 클라이언트 데이터 의 포인터 이다
** 가상 테이블 모듈 에서 xCreate 및 특정 연결 ] 메서드 에
** 새로운 가상 테이블을 만들거나 다시 초기화 되어도 되는 경우 .
**
** ^ sqlite3_create_module_v2 ( ) 인터페이스는 번째 매개 변수를 가지고
** pClientData 의 소멸자 에 대한 포인터 이다. ^ SQLite 는 의지
** ( 그것이 NULL이 아닌 경우 ) 소멸자 함수 를 호출 할 때 SQLite
** 더 이상 pClientData 포인터를 필요로 하지 않습니다. ^ 소멸자 도됩니다
sqlite3_create_module_v2 ( ) 의 호출이 실패 했을 경우 ** 호출된다.
** ^ sqlite3_create_module ( )
** 인터페이스 는 NULL ) ( sqlite3_create_module_v2 와 동일합니다
** 소멸자 .
* /
SQLITE_API int sqlite3_create_module(
  sqlite3 *db,               /* SQLite connection to register module with */
  const char *zName,         /* Name of the module */
  const sqlite3_module *p,   /* Methods for the module */
  void *pClientData          /* Client data for xCreate/xConnect */
);
SQLITE_API int sqlite3_create_module_v2(
  sqlite3 *db,               /* SQLite connection to register module with */
  const char *zName,         /* Name of the module */
  const sqlite3_module *p,   /* Methods for the module */
  void *pClientData,         /* Client data for xCreate/xConnect */
  void(*xDestroy)(void*)     /* Module destructor function */
);

/ *
** CAPI3REF : 가상 테이블 인스턴스 개체
** KEYWORDS : sqlite3_vtab
**
** 모든 가상 테이블 모듈 구현은 하위 클래스를 사용 하고 있습니다
** 이 개체 의 특정 인스턴스를 설명하기 위해
** 가상 테이블 의 . 각 서브 클래스 입니다
** 모듈 구현 의 특정 요구에 맞게 조정한다.
** 이 슈퍼 클래스 의 목적은 특정 필드 를 정의 하기위한 것이다
** 모든 모듈의 구현에 공통된다.
**
** ^ 가상 테이블 방법을 지정하여 오류 메시지를 설정할 수 있습니다
** zErrMsg 에 [ sqlite3_mprintf ( ) ] 에서 입수 한 문자열입니다. 방법은 해야
** 사전 문자열 은 호출 에 의해 풀어 놓인 돌 걸릴 [ sqlite3_free 을 ( )
** 전 zErrMsg 에 새로운 문자열을 할당합니다. ^ 오류 메시지 후
** 는 클라이언트 응용 프로그램으로 전달 된 문자열이 자동으로 됩니다
** sqlite3_free ( 에 의해 발표 ) 과 zErrMsg 필드 가 제로가됩니다 .
* /
struct sqlite3_vtab {
  const sqlite3_module *pModule;  /* The module for this virtual table */
  int nRef;                       /* NO LONGER USED */
  char *zErrMsg;                  /* Error message from sqlite3_mprintf() */
  /* Virtual table implementations will typically add additional fields */
};

/ *
** CAPI3REF : 가상 테이블 커서 개체
** KEYWORDS : sqlite3_vtab_cursor { 가상 테이블 커서 }
**
** 모든 가상 테이블 모듈 구현은 하위 클래스를 사용 하고 있습니다
에 가리키는 커서를 설명하는 데 ** 다음과 같은 구조
** 가상 테이블을 사용하는
** 가상 테이블 을 반복 한다. 커서가 사용하여 만듭니다
** [ sqlite3_module.xOpen | XOPEN 모듈 방법 은 파괴된다
** [ sqlite3_module.xClose | XCLOSE ] 에 의한 방법 . 커서가 사용 되는
** [ xFilter , xNext , xEof , xColumn ] 및 [ xRowid ] 의 방법에 의해,
** 모듈 . 각 모듈 의 구현 을 정의합니다
** 커서 구조 의 함량은 자신의 요구 에 맞게.
**
** 이 슈퍼 클래스는 커서 의 필드 를 정의 하기 위해 존재하는 것
** 모든 구현 에 공통 하고있다.
* /
struct sqlite3_vtab_cursor {
  sqlite3_vtab *pVtab;      /* Virtual table of this cursor */
  /* Virtual table implementations will typically add additional fields */
};

/ * 
** CAPI3REF : 가상 테이블의 스키마를 선언합니다 
** 
의 ** ^ [xCreate 및 특정 연결]의 방법 
** 가상 테이블 모듈이 인터페이스를 호출 
** 형식 (열 이름과 데이터 형식)를 선언하는 
** 가상 테이블은 그들이 구현되어 있습니다. 
* /
SQLITE_API int sqlite3_declare_vtab(sqlite3*, const char *zSQL);

/ *
** CAPI3REF : 가상 테이블 에 대한 함수를 오버로드
**
** ^ ( 가상 테이블은 함수 의 대체 구현을 제공 할 수 있습니다
** 가상 테이블 모듈 에서 xFindFunction ] 메서드를 사용합니다.
이러한 기능 ** 이 글로벌 버전
오버로드 되기 때문 이다. ) ** ^ 존재 해야합니다
**
** ^ ( 이 API는 특정 가지는 함수 가 확실 글로벌 버전입니다
** 매개 변수 의 이름과 번호 가 존재 합니다. 그런 함수 가 없으면
이 API 를 호출하기 전에 ** 새로운 함수가 작성 됩니다. ) ^ ^ 구현
** 새로운 기능 을 항상 throw되는 예외 가 발생합니다. 이렇게
** 새로운 함수는 그 자체가 무엇을 위해 좋지 않습니다. 그 밖에
** 목적은 오버 로드 할 수있는 자리 표시 자 함수 인 것이 있다
** 가상 테이블 에서 .
* /
SQLITE_API int sqlite3_overload_function(sqlite3*, const char *zFuncName, int nArg);

/ *
** 위에서 정의 된 가상 테이블 기구 ( 의 인터페이스는 백업
** 이것과 매우 비슷한 의견) 에는 현재 간주됩니다
** 실험적 이라고 . 인터페이스는 호환되지 않는 방식으로 변경 될 수 있습니다.
** 이것은 당신을위한 문제 이면 이 시점 에서는 인터페이스를 사용 하지 마십시오 .
**
** 가상 테이블 기구가 안정되면 , 우리는 선언합니다
** 인터페이스는 고정 무기한 그것을 지원 하고 이 댓글을 삭제 하십시오.
* /

/ *
** CAPI3REF : 오픈 BLOB에 대한 핸들
** KEYWORDS : { BLOB 핸들 } { BLOB 핸들 }
**
** 이 개체의 인스턴스 는 위에 열려있는 BLOB 을 나타내는
** [ sqlite3_blob_open | 증분 BLOB I / O 를 할 수있다.
** ^ 이 형식의 개체는 sqlite3_blob_open ( ) 에 의해 만들어집니다
** 과 에 의해 파괴 [ sqlite3_blob_close ( ) .
** ^ [ sqlite3_blob_read ( ) 및 sqlite3_blob_write ( ) 인터페이스
** BLOB 의 작은 하위 섹션 을 읽고 쓸 수 있습니다.
** ^ [ sqlite3_blob_bytes ( ) 인터페이스는 바이트 단위로 BLOB 의 크기를 반환합니다.
* /
typedef struct sqlite3_blob sqlite3_blob;

/ *
** CAPI3REF : 증분 나의 경우 BLOB 을 열기 / O
**
** ^ ( 이 인터페이스 가 열리고 BLOB 핸들을 | 핸들 로 있고 BLOB 에
** 행 irow 에서는 열 zColumn 데이터베이스 ZDB 테이블 zTable ;
** 즉, 에 의해 선택 되는 것이다 동일한 BLOB .
**
** <PRE>
** zDb.zTable [ ROWID ] = 는 IRow . SELECT zColumn ;
** < / pre > 의 ) ^
**
flags 매개 변수 가 제로가 아닌 경우 ** ^ 그리고 BLOB 읽기 용으로 오픈 된
** 및 쓰기 권한입니다. 그것이 제로의 경우는 ^ BLOB 을 읽기 액세스를 위해 열려 있다.
** ^ 이것은 인덱스 또는 기본 의 일부인 열을 열 수 없습니다
** 버너 의 키 . 외래 키 제약 조건 이 활성화 되어 있으면 ^ 그렇습니다
쓰기 용 하위 키 의 일부인 열을 열 수 없습니다. **
**
** ^ 데이터베이스 이름이 포함 된 파일 이름 이 아님 에 주의 하십시오
** 데이터베이스 가 아닌 데이터베이스의 고유 이름 이라는
데이터베이스는 첨부를 이용하여 연결 할 때 ** AS 키워드 다음에 표시 됩니다.
** ^ 메인 데이터베이스 파일 의 경우 데이터베이스 이름 은 "기본" 입니다.
** ^ 임시 테이블 의 경우 , 데이터베이스 이름은 " TEMP " 입니다.
**
** ^ ( 성공 하면 SQLITE_OK ] 를 반환하고 새 BLOB 핸들 ] 은 써진
** 에 * ppBlob . 그렇지 않은 경우 오류 코드 를 반환 * ppBlob 가 설정되어 있다
** 널 포인터 로 . ) ^
** ^ 이 기능은 데이터베이스 연결 오류 코드와 메시지를 설정합니다
** [ sqlite3_errcode ( ) 및 sqlite3_errmsg ( ) 와 관련 을 통해 액세스
** 기능 . ^ * ppBlob 변수 는 항상 초기화 되는 점에 유의 하십시오
** 호출 하는 것이 안전 합니다 같이 [ ( sqlite3_blob_close 을 ) ] * 의 ppBlob 에
** 불구하고, 이 루틴이 성공했는지 실패 했어.
**
** ^ ( 만약 BLOB 핸들 포인트 에 의해 수정 된 것을 행
** 업데이트, 삭제 또는 부작용 [ 분쟁에 관한 ] 에서
" 만료 "로 ** 다음 BLOB 핸들이 표시되어 있습니다.
행 의 모든 열 이 변경된 경우 ** 이것은 짝수 열 진실 이다
** 1 이외의 BLOB 핸들 위에 열려있다. ) ^
** ^ 는 [ sqlite3_blob_read ( ) 및 sqlite3_blob_write ( ) 에 대한 호출
** 만료 된 BLOB 핸들은 [ SQLITE_ABORT ] 반환 코드 와 함께 실패 합니다.
** ^ ( 이전 BLOB 만료 BLOB 에 기록 된 변경 은 없습니다
** BLOB 의 만료로 인하여 롤백 되었습니다 . 이러한 변화는 궁극적으로 의지
** 트랜잭션이 완료 될 때까지 계속 한 경우 커밋 . ) ^
**
** ^ 크기 를 결정하기 위해 [ sqlite3_blob_bytes ( ) 인터페이스를 사용하여
** 에 오픈 한 BLOB . ^ 방울 의 크기는 이로 인하여 변경할 수 없습니다
** 인터페이스. 크기 를 변경하려면 새로 고침 SQL 명령을 사용 합니다.
** 방울 .
**
** ^ [ sqlite3_blob_open ( ) 인터페이스는 , ROWID 없음 ] 때문에 실패 합니다
** 테이블. 증분 BLOB I / O는 없음 ROWID 테이블 에서 는 불가능하다.
**
** ^ [ sqlite3_bind_zeroblob ( ) 및 sqlite3_result_zeroblob ( ) 인터페이스
** 및 임베디드 원하는 경우 [ zeroblob ] SQL 함수를 사용할 수있다 ,
** 읽거나 사용하여 쓰고있는 하늘, 제로화 방울 만들기
** 이 인터페이스 .
**
** 리소스 누수 모든 오픈 [ BLOB 핸들 을 피하기 위해 해야 할 궁극적으로
** [ sqlite3_blob_close ( ) 를 호출하여 해제 된다.
* /
SQLITE_API int sqlite3_blob_open(
  sqlite3*,
  const char *zDb,
  const char *zTable,
  const char *zColumn,
  sqlite3_int64 iRow,
  int flags,
  sqlite3_blob **ppBlob
);
/ *
** CAPI3REF : 새 행에 BLOB 핸들을 이동
**
** ^ 이 함수는 그것이 가리 키도록 기존 BLOB 핸들을 이동 하는 데 사용 되는
** 동일한 데이터베이스 테이블 의 다른 행 에 . ^ 새로운 행이 특정 된
** 둘째 인수 로 전달 된 ROWID 값 . 행만 수 있습니다
** 변경 . ^ 방울 핸들 이 열려있는 데이터베이스 테이블 및 열
** 동일하게 유지 . 새 줄에 기존 의 BLOB 핸들을 움직이면 수 있습니다
** 기존 의 핸들을 닫고 새 항목 을 열 더 빠르다.
**
** ^ ( 새 줄이 sqlite3_blob_open ( ) 와 같은 기준을 충족 해야합니다 -
** 그것이 존재 하고있을 필요 가 있고, 안에 저장된 BLOB 또는 텍스트 값 중 하나가 있어야한다
** 후보 라인. ) ^ ^ 새 행이 테이블 에 존재 하거나 되지 않는 경우
** 그것은 BLOB 또는 텍스트 값이 포함되어 있거나 다른 오류가 발생 하면 하지
** SQLite 오류 코드 를 반환하고 방울 핸들이 중지 된 것으로 간주됩니다 .
** ^ 에 대한 모든 후속 호출 [ sqlite3_blob_read ( ) , sqlite3_blob_write ( ) 또는
** [ sqlite3_blob_reopen ( ) ] 중단 된 BLOB 에 다시 즉시 해결
** SQLITE_ABORT . ^ 중단 된 BLOB 핸들 의 sqlite3_blob_bytes 을 ( ) 호출
** 항상 제로 를 돌려줍니다.
**
** ^ 이 함수는 데이터베이스 핸들 오류 코드와 메시지를 설정합니다.
* /
SQLITE_API SQLITE_EXPERIMENTAL int sqlite3_blob_reopen(sqlite3_blob *, sqlite3_int64);

/ *
** CAPI3REF : BLOB 핸들 닫기
**
** ^ 오픈 [ BLOB 핸들을 ] 닫습니다.
**
** ^ BLOB 닫기 현재 트랜잭션이 커밋 시켜야 한다
다른 BLOB 는 존재하지 않는 경우 ** 보류중인 문장 을 제공 하지 않고 ,
** 데이터베이스 연결 이 자동 커밋 모드 이다.
** ^ 어떤 게시물 이 BLOB 에 행해진 경우 캐시에 보관 될 수 있습니다
** 그들이 적합한 경우에는 가까운 작업이 이루어질 때까지 .
**
** ^ ( BLOB 을 닫으면 자주 변경 을 강제로
** 디스크에 임의 의 I / O 오류 가 발생한 경우, 그들은 아마 발생합니다
** 시 BLOB 를 닫을 때 . 중에 발생한 오류
** 폐쇄 는 0이 아닌 리턴 값으로 보고되고 있습니다. ) ^
**
** ^ ( BLOB 가 . 무조건 닫혀있는 경우에도 이 반환
** 오류 코드가 BLOB 가 아직 닫혀 있다. ) ^
**
** ^ 널 포인터 (같은 루틴 을 호출 하여 반환 된
** 에 실패한 통화에서 sqlite3_blob_open ( ) ] ) 무해 아무것도 하지 않습니다.
* /
SQLITE_API int sqlite3_blob_close(sqlite3_blob *);

/ * 
** CAPI3REF : 오픈 BLOB의 크기를 반환 
** 
** ^ 통해 액세스 BLOB의 크기를 바이트 단위로 돌려줍니다 
** 성공하고 유일한 인수 [BLOB 핸들을] 열렸다. ^ 
** 증분 방울 I / O 루틴을 읽을 수하거나 덮어 기존의 
** 방울 콘텐츠 그들은 BLOB의 크기를 변경할 수 없습니다. 
** 
**이 루틴은 생성 된 [BLOB 핸들에서 작동합니다 
** [sqlite3_blob_open () 및 그 전에 호출이 성공에 의한 것이 있습니다 
**에 의해 폐쇄되고, (sqlite3_blob_close). 내의 다른 포인터를 건네 준다 
** 미정 아마도 바람직하지 않은 행동이 루틴의 결과. 
* /
SQLITE_API int sqlite3_blob_bytes(sqlite3_blob *);

/ *
** CAPI3REF : 증분 BLOB 로부터 읽어 내진 데이터
**
** ^ ( 이 기능은 오픈 [ BLOB 핸들 ] 에서 데이터를 읽는 데 사용 되는 에
** 호출자가 제공하는 버퍼 를 . 데이터 의 N 바이트 는 Z 버퍼 로 복사 된다
** 오픈 BLOB 에서 오프셋 IOFFSET 에서 시작된다. ) ^
**
** ^ 오프셋 IOFFSET N 은 BLOB 의 마지막 에서 바이트 보다 작은 경우
** [ SQLITE_ERROR ] 를 반환하고 데이터 가 로드 되지 않습니다. ^ 만약 N 또는 IOFFSET 입니다
** 제로 미만 , SQLITE_ERROR ] 를 반환하고 데이터 가 로드 되지 않습니다.
** ^ 방울 의 크기 ( 따라서 N + IOFFSET 의 최대 값 )
** [ sqlite3_blob_bytes ( ) 인터페이스를 사용하여 결정할 수 있다.
**
** ^ 만료 의 BLOB 핸들 ] 에서 읽기 에 실패 하고 실패
** [ SQLITE_ABORT ] 오류 코드.
**
** ^ ( 성공한 경우 sqlite3_blob_read ( ) 는 SQLITE_OK 을 반환합니다.
** 그렇지 않으면 오류 코드 또는 확장 오류 코드 가 반환됩니다. ) ^
**
** 이 루틴은 생성 된 [ BLOB 핸들 에서 작동합니다
** [ sqlite3_blob_open ( ) 및 그 전에 호출이 성공 에 의한 것이 있습니다
** 에 의해 폐쇄 되고 , ( sqlite3_blob_close ) . 내의 다른 포인터를 건네 준다
** 미정 아마도 바람직하지 않은 행동 이 루틴 의 결과 .
**
** 참조 : [ sqlite3_blob_write 을 ( ) .
* /
SQLITE_API int sqlite3_blob_read(sqlite3_blob *, void *Z, int N, int iOffset);

/ *
** CAPI3REF : 증분 BLOB 에 데이터를 기록
**
더 ** ^ 이 기능은 오픈 [ BLOB 핸들 로 데이터를 쓰는 데 사용 됩니다
** 호출자가 제공하는 버퍼 를 . ^ 데이터 의 N 바이트 Z 버퍼 에서 복사
** 오픈 BLOB 오프 IOFFSET 에서 시작된다.
**
** ^ 첫 번째 인수로 전달 된 [ BLOB 핸들 ] 을 위해 열려 있지 않은 경우
** ( ( ) sqlite3_blob_open ] 제로 였다 에 flags 매개 변수 ) 를 기록 ,
** 이 함수는 SQLITE_READONLY 을 반환합니다.
**
** ^ 이 함수는 BLOB 의 내용을 변경할 수 있으며, 그것은이다
** 불가능 이 API를 사용하여 BLOB 의 크기를 늘립니다.
** ^ 오프셋 IOFFSET N 은 BLOB 의 마지막 에서 바이트 보다 작은 경우
** [ SQLITE_ERROR 가 반환 되고 데이터는 기록되지 않습니다. ^ 만약 N 이
** 0보다 [ SQLITE_ERROR 가 반환 되고 데이터는 기록되지 않습니다.
** BLOB 의 크기 ( 따라서 N + IOFFSET 의 최대 값 )
** [ sqlite3_blob_bytes ( ) 인터페이스를 사용하여 결정할 수 있다.
**
** ^ 만료 의 BLOB 핸들 ]에 쓰기 에 실패 하고 실패
** [ SQLITE_ABORT ] 오류 코드. ^ 발생한 BLOB 에 씁니다
** 만료 후 BLOB 핸들 에서 롤백 되지 않습니다 전에
핸들 ** 만료 물론 그 변화 는 모르지만
** BLOB 핸들을 만료 문장 에 의해 무시 되고있다
** 또는 다른 독립적 인 문장 에 의한 다.
**
** ^ ( 성공한 경우 sqlite3_blob_write ( ) 는 SQLITE_OK 을 반환합니다.
** 그렇지 않으면 오류 코드 또는 확장 오류 코드 가 반환됩니다. ) ^
**
** 이 루틴은 생성 된 [ BLOB 핸들 에서 작동합니다
** [ sqlite3_blob_open ( ) 및 그 전에 호출이 성공 에 의한 것이 있습니다
** 에 의해 폐쇄 되고 , ( sqlite3_blob_close ) . 내의 다른 포인터를 건네 준다
** 미정 아마도 바람직하지 않은 행동 이 루틴 의 결과 .
**
** 참조 : [ sqlite3_blob_read 을 ( ) .
* /
SQLITE_API int sqlite3_blob_write(sqlite3_blob *, const void *z, int n, int iOffset);

/ *
** CAPI3REF : 가상 파일 시스템 오브젝트
**
** 가상 파일 시스템 ( VFS ) 는 [ sqlite3_vfs 개체 이다
** 그 SQLite 는 상호 작용하는 데 사용
** 기본 운영 체제 와 . 가장 SQLite 는 함께 빌드
** 호스트 시스템에 적합한 단일 기본 VFS .
** NEW VFSes 등록 할 수 기존 VFSes 등록이 취소 할 수 있습니다.
** 다음 인터페이스 가 포함되어 있습니다.
**
** ^ sqlite3_vfs_find ( ) 인터페이스는 지정된 이름 의 VFS 에 대한 포인터를 돌려 준다.
** ^ 이름 은 대소 문자 를 구분 합니다.
** ^ 이름은 제로로 종료 하는 UTF - 8 문자열입니다.
일치하는 경우 ** ^ NULL 포인터 가 반환된다.
** ^ 만약 zVfsName 기본 VFS 가 반환 된 NULL입니다.
**
** ^ 새로운 VFSes 는 sqlite3_vfs_register ( ) 에 등록되어 있다.
makeDflt 플래그가 설정되어 있는 경우 ** ^ 각각의 새로운 VFS는 기본 VFS 됩니다.
** ^ 같은 VFS 가 부상 하지 않고 여러 번 등록 할 수 있습니다.
** ^ 기본 VFS 기존 VFS 를 만들려면 다시 등록
** makeDflt 플래그가 설정 되었다. 만약 2 가지 VFSes
** 같은 이름 은 거동이 정의 되지 않은 등록 되어 있다. 만약
** VFS 가 NULL 의 이름 또는 빈 문자열 에 등록되어 있는 ,
** 다음 동작은 미정 도리 입니다.
**
** ^ sqlite3_vfs_unregister ( ) 인터페이스를 VFS 의 등록을 취소 합니다.
기본 VFS 가 등록되지 않은 경우 ** ^ ( 다른 VFS는 다음과 같이 선택 됩니다
** 기본 . 새로운 VFS 를위한 선택 은 선택 사항입니다. ) ^
* /
SQLITE_API sqlite3_vfs *sqlite3_vfs_find(const char *zVfsName);
SQLITE_API int sqlite3_vfs_register(sqlite3_vfs*, int makeDflt);
SQLITE_API int sqlite3_vfs_unregister(sqlite3_vfs*);

/ *
** CAPI3REF : 뮤텍스
**
** SQLite 코어 는 스레드 마다 이러한 루틴 을 사용 하고 있습니다
** 동기화 . 그들은 내부 를 대상으로하고 있습니다 만
** SQLite 의 의한 사용, SQLite 반면 링크 코드
**이 루틴 중 하나를 사용 하는 것을 허용 .
**
** SQLite 의 소스 코드는 복수의 구현이 포함되어 있습니다
**이 뮤텍스 루틴 . 적절한 구현
** 는 컴파일시 에 자동으로 선택 됩니다. ^ (이하
** 구현은 SQLite 코어 로 볼 수 있습니다.
**
** <UL>
** <LI> 의 SQLITE_MUTEX_PTHREADS
** <LI> SQLITE_MUTEX_W32
** <LI> SQLITE_MUTEX_NOOP
** < / UL > ) ^
**
** ^ SQLITE_MUTEX_NOOP 구현 루틴 세트입니다.
** 진실한 잠금을 하지 않고 에서 사용하기에 적합합니다
** 단일 스레드 응용 프로그램 . ^ SQLITE_MUTEX_PTHREADS 과
** SQLITE_MUTEX_W32 구현은 Unix 에서 사용 에 적합합니다
** 및 Windows .
**
** ^ ( SQLite 는 SQLITE_MUTEX_APPDEF 전처리를 사용하여 컴파일 된 경우
** 매크로 ( " = 1 - DSQLITE_MUTEX_APPDEF " 에서 ) 정의 는 무엇 뮤텍스 응
** 구현은 라이브러리 에 포함되어 있습니다. 이 경우
** 응용 프로그램을 사용하여 사용자 지정 뮤텍스 의 구현을 제공 해야 합니다
sqlite3_config ( ) 함수 ** [ SQLITE_CONFIG_MUTEX 옵션
** sqlite3_initialize ( ) 및 기타 공공 sqlite3_ 를 호출하기 전에
** sqlite3_initialize ( ) 를 호출하는 함수 ) . ^
**
** ^ sqlite3_mutex_alloc ( ) 루틴은 새로 할당
** 뮤텍스 그 포인터를 돌려 준다. ^ 그것은 NULL을 반환하는 경우
** 그것이 mutex 를 할당 할 수 없음 을 의미합니다. ^ SQLite는
** 스택 을 해제 하고 ​​오류를 반환합니다. ^ ( 인수
** ( sqlite3_mutex_alloc 에 ) 이 정수 상수 중 하나 입니다.
**
** <UL>
** <LI> SQLITE_MUTEX_FAST
** <LI> SQLITE_MUTEX_RECURSIVE
** <LI> SQLITE_MUTEX_STATIC_MASTER
** <LI> SQLITE_MUTEX_STATIC_MEM
** <LI> SQLITE_MUTEX_STATIC_MEM2
** <LI> SQLITE_MUTEX_STATIC_PRNG
** <LI> SQLITE_MUTEX_STATIC_LRU
** <LI> SQLITE_MUTEX_STATIC_LRU2
** < / UL > ) ^
**
** ^ 처음 두 상수 ( SQLITE_MUTEX_FAST 과 SQLITE_MUTEX_RECURSIVE )
** 원인 sqlite3_mutex_alloc ( ) 를 만들
** 새로운 뮤텍스 . ^ 새로운 mutex 는 재귀 때 SQLITE_MUTEX_RECURSIVE
** 반드시 이렇게 SQLITE_MUTEX_FAST 가 사용되는 때 사용된다 .
** 뮤텍스 의 구현은 구별 을 할 필요가 없습니다.
** SQLITE_MUTEX_RECURSIVE 과 SQLITE_MUTEX_FAST 간 동의 가없는 경우
** 싶지 않아요. ^ SQLite 는 그냥 재귀 적 뮤텍스를 요청 합니다
** 정말 1 을 필요로하는 경우 . ^ 만약 빨리 비 재귀 적 뮤텍스
** 구현 은 호스트 플랫폼 뮤텍스 서브 시스템 에서 볼 수 있습니다
** SQLITE_MUTEX_FAST 에 따라 이 같은 뮤텍스를 반환 할 수 있습니다.
**
** ^ sqlite3_mutex_alloc 다른 허용 된 매개 변수 ( ) ( 이외의 것
** SQLITE_MUTEX_FAST 과 SQLITE_MUTEX_RECURSIVE 보다 ) 각 반환
** 정적 기존 의 뮤텍스 의 포인터. ^ 여섯 정적 뮤텍스입니다
** SQLite는 현재 버전 에서 사용 된다. SQLite 는 이후 버전
** 추가 정적 뮤텍스를 추가 할 수 있습니다. 정적 뮤텍스는 내부 용 입니다
** 의 SQLite 에서만 사용 합니다. SQLite는 뮤텍스를 사용하는 응용 프로그램 은 해야
** 사용하는 유일한 역동적 인 mutex 는 SQLITE_MUTEX_FAST 의한 반품
** SQLITE_MUTEX_RECURSIVE .
**
** ^ 주의 하고 만약 동적 뮤텍스 매개 변수 ( SQLITE_MUTEX_FAST 1
** 또는 SQLITE_MUTEX_RECURSIVE ) 가 다음 사용 된 sqlite3_mutex_alloc ( )
** 모든 호출 에 다른 뮤텍스를 반환합니다. ^ 그러나 정적 위한
** 뮤텍스 유형은 동일한 뮤텍스를 가진 모든 호출 에서 반환됩니다
** 동일한 유형 번호.
**
** ^ sqlite3_mutex_free ( ) 루틴은 이전 할당 을 해제
** 동적 뮤텍스를 할당 했다. ^ SQLite 는 모든 할당 을 해제 하도록 주의 합니다.
** 그것이 할당 동적 뮤텍스 . 역동적 인 mutex 는 존재할 수 없습니다
이러한 할당 이 해제 될 때 ** 사용 하고 있습니다 . 정적 할당 을 해제 하려고 하면
정의되지 않은 동작 ** 뮤텍스 결과 . ^ SQLite 는 할당 을 해제 하지 않은
** 정적 뮤텍스 .
**
** ^ sqlite3_mutex_enter ( ) 와 sqlite3_mutex_try 는 ( ) 시도 루틴
** 뮤텍스 에 들어갑니다. ^ 다른 스레드 가 뮤텍스 에 이미 있는 경우
** sqlite3_mutex_enter ( ) 을 차단하고 sqlite3_mutex_try ( ) 를 돌려줍니다
** SQLITE_BUSY . ^ sqlite3_mutex_try ( ) 인터페이스 로 돌아가려면 SQLITE_OK ]
** 성공적인 진입 에 의존한다. ^ ( 뮤텍스를 사용하여 만든
** SQLITE_MUTEX_RECURSIVE 은 동일한 스레드에서 여러 번 입력 할 수 있습니다.
** 이런 경우 에는
** 뮤텍스가 다른 스레드 전에 동일한 횟수를 종료 해야
** 입력 할 수 있습니다. ) ^ ^ ( 같은 스레드는 다른 에 들어 가려고 하는 경우
** 번 이상 뮤텍스 의 종류 는 동작은 미정 도리 입니다.
** SQLite 는 전시 하는 것은 아닙니다
뮤텍스 의 자신의 바쁜 ** 이러한 동작 ) . ^
**
** ^ ( 일부 시스템 에서는 (예 : Windows 95 ) 은 작업을 지원 하지 않습니다
** sqlite3_mutex_try 의해 구현 ( ) . 이러한 시스템 에서는 sqlite3_mutex_try ( )
** 항상 SQLITE_BUSY 을 반환합니다. SQLite 의 핵심 은 지금 까지 사용 하고 있습니다
** 최적화 등 의 sqlite3_mutex_try 는 ( ) 때문에, 이것은 허용 된 동작입니다. ) ^
**
** ^ sqlite3_mutex_leave ( ) 루틴은 뮤텍스를 종료
** 이전에 같은 스레드에 의해 작성 되었다. ^ ( 행동
뮤텍스가 현재 입력 되어 있지 않은 경우 ** 정의 되어 있지 않습니다
** 스레드 를 호출하거나 현재 할당되지 않는다. SQLite 는 의지
** 중 하나를 수행 하지 않습니다. ) ^
**
** ^ 인수가 sqlite3_mutex_enter 한 경우 ( ) sqlite3_mutex_try ( ) 또는
** sqlite3_mutex_leave ( ) 는 NULL 포인터 인 모든 3 개의 루틴
** 하늘 명령어로 작동합니다.
**
** 참조 : [ sqlite3_mutex_held ( ) 및 sqlite3_mutex_notheld ( ) .
* /
SQLITE_API sqlite3_mutex *sqlite3_mutex_alloc(int);
SQLITE_API void sqlite3_mutex_free(sqlite3_mutex*);
SQLITE_API void sqlite3_mutex_enter(sqlite3_mutex*);
SQLITE_API int sqlite3_mutex_try(sqlite3_mutex*);
SQLITE_API void sqlite3_mutex_leave(sqlite3_mutex*);

/ *
** CAPI3REF : 뮤텍스 개체 의 메서드
**
** 이 구조체 의 인스턴스는 낮은 수준의 루틴을 정의
** 뮤텍스를 할당 하여 사용 하는 데 사용 된다.
**
** 일반적으로 SQLite 가 제공하는 기본 뮤텍스 의 구현이 있습니다
** 충분하지만 사용자 는 사용자 를 할당 하는 옵션이 있습니다
** 특수 배포 및 시스템 구현 한 SQLite 를위한
** 적절한 구현을 제공 하지 않습니다. 이 경우 사용자
** 만들고 전달하기 위해 이 구조체 의 인스턴스를 채 웁니다
** [ SQLITE_CONFIG_MUTEX 옵션 과 함께 ( ) sqlite3_config 한다.
** 또한이 구조체 의 인스턴스 로 사용할 수있다
현재 뮤텍스 시스템 을 검색 하고 ** 출력 변수 때
** 구현 , SQLITE_CONFIG_GETMUTEX 옵션을 사용합니다.
**
** ^ 이 구조 에 의해 정의 xMutexInit 방법은 다음과 같이 불려
** sqlite3_initialize ( ) 함수는 시스템 초기화 의 일부 .
** ^ xMutexInit 루틴 은 각각 한 번만 SQLite 에 의해 불려갑니다
[ sqlite3_initialize ( ) 에 ** 효과적인 통화 .
**
** ^ 이 구조 에 의해 정의 xMutexEnd 방법은 다음과 같이 불려
** sqlite3_shutdown ( ) 함수는 시스템 종료 의 일부 . 더
** 이 메소드의 구현 은 모든 미처리 을 출시 될 예정입니다
** 뮤텍스 법 의 구현 에 의해 얻어진 자원, 특히
** xMutexInit 방법 에 의해 얻어진 것이다. ^ xMutexEnd ( )
** 인터페이스는 [ sqlite3_shutdown ( ) 를 호출 할 때마다 한 번만 호출됩니다.
**
** ^ ( 이 구조체 ( xMutexAlloc 에 의해 정의 된 나머지 7 가지 방법 ,
** xMutexFree , xMutexEnter , xMutexTry , xMutexLeave , xMutexHeld 과
** xMutexNotheld ) 다음 인터페이스 ( 각각 ) 을 구현합니다.
**
** <UL>
** <LI> [ sqlite3_mutex_alloc ( ) < / LI >
** <LI> [ sqlite3_mutex_free ( ) < / LI >
** <LI> [ sqlite3_mutex_enter ( ) < / LI >
** <LI> [ sqlite3_mutex_try ( ) < / LI >
** <LI> [ sqlite3_mutex_leave ( ) < / LI >
** <LI> [ sqlite3_mutex_held ( ) < / LI >
** <LI> [ sqlite3_mutex_notheld ( ) < / LI >
** < / UL > ) ^
**
** 유일한 차이점은 공용 sqlite3_XXX 함수 가 열거 이라는 것입니다
** 상기 침묵 대신 NULL 포인터를 전달 임의 의 호출을 무시
** 유효한 뮤텍스 핸들 . 정의 된 메서드 의 구현
** 이 구조는 이 사건을 처리 할 필요가 없지만 결과
** 대신 유효한 뮤텍스 핸들 NULL 포인터를 전달하는 정의 되지 않습니다
** (즉, 그것은 경우 에 분할 오류 구현 을 제공하기 위해 허용되는
** 는 ) NULL 포인터가 전달됩니다.
**
** xMutexInit ( ) 메소드는 스레드로부터 안전 해야 합니다. ^ 그것은 무해 해야한다
동일한 프로세스 및 배 ** ) ( xMutexInit 를 호출 여러 번
** xMutexEnd 의 호출 을 개입 ( ) . 눈 후속 호출
** xMutexInit ( ) 는 - OPS는 안됩니다.
**
** ^ xMutexInit ( ) 는 SQLite 메모리 할당 ( sqlite3_malloc 를 ( ) 를 사용 해서는 안
** 및 계열사 ) . ^ 마찬가지로 xMutexAlloc ( ) SQLite 의 메모리 를 사용 해서는 안
** 정적 뮤텍스 할당. ^ 그러나 xMutexAlloc ( ) SQLite 를 사용 할 수 있습니다
** 고속 또는 재귀 적 뮤텍스 의 메모리 할당 .
**
[ sqlite3_shutdown 는 ( ) 의 경우 ** ^ SQLite 는 xMutexEnd ( ) 메서드를 호출합니다
** 라고하지만 , xMutexInit 전에 호출이 SQLITE_OK 를 돌려 주었을 경우 에 한합니다.
xMutexInit 어떻게 든 실패하면 ** 자체 의 뒤처리 것으로 예상 되는
** 가기 전에.
* /
typedef struct sqlite3_mutex_methods sqlite3_mutex_methods;
struct sqlite3_mutex_methods {
  int (*xMutexInit)(void);
  int (*xMutexEnd)(void);
  sqlite3_mutex *(*xMutexAlloc)(int);
  void (*xMutexFree)(sqlite3_mutex *);
  void (*xMutexEnter)(sqlite3_mutex *);
  int (*xMutexTry)(sqlite3_mutex *);
  void (*xMutexLeave)(sqlite3_mutex *);
  int (*xMutexHeld)(sqlite3_mutex *);
  int (*xMutexNotheld)(sqlite3_mutex *);
};

/ *
** CAPI3REF : 뮤텍스 유효성 검사 루틴
**
** sqlite3_mutex_held ( ) 와 sqlite3_mutex_notheld ( ) 루틴
** 이 주장 ( ) 문에서 사용 하기위한 것입니다. ^ SQLite 코어
** 주장 안쪽 을 제외하고 이러한 루틴 을 사용 하지 않습니다 ( ) 와 응용 프로그램
** 핵심 리드 에 따르는 것이 좋습니다. ^ SQLite 의 코어 만
그것은 컴파일 된 때 **이 루틴 의 구현을 제공 합니다
** SQLITE_DEBUG 플래그 를 갖는다. ^ 외부 뮤텍스 구현
** 만 SQLITE_DEBUG 인 경우 이러한 루틴을 제공 해야 합니다
** 정의 되어 NDEBUG 가 정의 되어 있지 않은 경우.
**
** ^ 이러한 루틴은 true를 반환해야하는 경우 해당 인수 에 뮤텍스
** 는 호출 스레드 가 각각 개최 된 개최 된지 되지 않습니다.
**
** ^ 구현은 이 버전 을 제공 할 필요는 없다
** 실제로 작동 하는 루틴 . 구현 이 작동 제공 하지 않는 경우
**이 루틴 버전 은 최소한 스텁 을 제공 해야한다 라고는 할 수
1 스퓨리어스 어설 션 오류가 들어오지 않게 ** true를 돌려 준다.
**
** ^ 인수가 sqlite3_mutex_held 할지 의 ( ) 는 NULL 포인터가 있는
** 이 루틴은 1 을 반환해야 합니다. 이것은 이후 어긋 보인다
그것이 없으면 ** 분명히 뮤텍스를 보유 할 수 없습니다. 그러나
빌드 가 아니므 ** 뮤텍스가 존재 하지 않는 이유 는
** 뮤텍스를 사용. 그리고 우리 는 포함 ) ( 주장 싶지 않아
** ( ) 가 실패 sqlite3_mutex_held 에 호출하기 때문에 0이 아닌 리턴 이
** 하려면 적절한 것. ^ sqlite3_mutex_notheld ( )
NULL 포인터를 지정할 때 ** 인터페이스 도 1 을 반환해야 합니다.
* /
#ifndef NDEBUG
SQLITE_API int sqlite3_mutex_held(sqlite3_mutex*);
SQLITE_API int sqlite3_mutex_notheld(sqlite3_mutex*);
#endif

/ * 
** CAPI3REF : mutex 형 
** 
** [sqlite3_mutex_alloc는 () 인터페이스는 단일 인수를 취 
**이 정수의 하나이다. 
** 
** 정적 뮤텍스의 집합은있는 SQLite 릴리스에서 변경 될 수 
** 다음. 내장 된 뮤텍스 논리를 덮어 응용 프로그램이어야합니다 
** 추가 정적 뮤텍스에 대응하기 위해서 준비했습니다. 
* /
#define SQLITE_MUTEX_FAST             0
#define SQLITE_MUTEX_RECURSIVE        1
#define SQLITE_MUTEX_STATIC_MASTER    2
#define SQLITE_MUTEX_STATIC_MEM       3  /* sqlite3_malloc() */
#define SQLITE_MUTEX_STATIC_MEM2      4  /* NOT USED */
#define SQLITE_MUTEX_STATIC_OPEN      4  /* sqlite3BtreeOpen() */
#define SQLITE_MUTEX_STATIC_PRNG      5  /* sqlite3_random() */
#define SQLITE_MUTEX_STATIC_LRU       6  /* lru page list */
#define SQLITE_MUTEX_STATIC_LRU2      7  /* NOT USED */
#define SQLITE_MUTEX_STATIC_PMEM      7  /* sqlite3PageMalloc() */
/ * 
** CAPI3REF : 데이터베이스 연결 뮤텍스를 획득 
** 
** ^이 인터페이스 포인터를 반환 [sqlite3_mutex 개체 그 
** 데이터베이스 연결에 대한 액세스를 직렬화하고 인수로 주어진 
** 스레드 모드 직렬화 될 때. 
** ^ 스레드 모드는 단일 스레드 또는 다중 스레드의 경우이 
**이 루틴은 NULL 포인터를 반환합니다. 
* /
SQLITE_API sqlite3_mutex *sqlite3_db_mutex(sqlite3*);

/ / *
** CAPI3REF : 저수준 제어 데이터베이스 파일
**
** ^ [ sqlite3_file_control ( ) 인터페이스는 에 직접 전화를합니다
** 관련 [ sqlite3_io_methods 개체 의 xFileControl 방법
** 둘째 인수 로 식별되는 특정 데이터베이스를 가진다. ^
** 데이터베이스 의 이름을위한 주요 데이터베이스 및 " TEMP "를위한 "주" 이다
** TEMP 데이터베이스 또는 를위한 AS 키워드 다음에 표시되는 이름
** [ 첨부 ] SQL 명령을 사용하여 추가 된 데이터베이스 .
** ^ NULL 포인터가 가리키는 위해 '기본' 대신 사용할 수있다
** 기본 데이터베이스 파일.
** ^ 이 루틴 의 세 번째 및 네 번째 매개 변수
** 는의 두 번째 및 세 번째 매개 변수에 전달 직접 전달
** xFileControl 방법 . ^ xFileControl 반환
** 메서드는이 루틴 의 반환 값 입니다.
**
** ^ op 매개 변수 의 원인을 SQLITE_FCNTL_FILE_POINTER 값
** [ sqlite3_file ] 의 기초가되는 개체 에 대한 포인터 에 기록되는
** 공간 은 네 번째 매개 변수가 가리키는 . ^ SQLITE_FCNTL_FILE_POINTER
** 경우 실제로는 실행 하지 않습니다 짧은 경로 이다
** sqlite3_io_methods.xFileControl 법 의 기초가된다.
**
** ^ 번째 매개 변수 ( zDbName ) 는 임의의 이름 과 일치하지 않는 경우
** 오픈 데이터베이스 파일 이 다음 SQLITE_ERROR 가 반환됩니다. ^ 이 오류
** 코드 는 [ ) sqlite3_errcode ( ] 기억 되지 않습니다 에게 리콜 되는 것은 아닙니다
** 또는 sqlite3_errmsg ( ) . 기초 xFileControl 법 마이트
** 도 SQLITE_ERROR 을 돌려 준다. 구별 할 방법이 없습니다
정확하지 않은 zDbName 와 그 아래 에서 SQLITE_ERROR 반환
** xFileControl 방법 .
**
** 참조 : [ SQLITE_FCNTL_LOCKSTATE ]
* /
SQLITE_API int sqlite3_file_control(sqlite3*, const char *zDbName, int op, void*);

/ *
** CAPI3REF : 테스트 인터페이스
**
** ^ sqlite3_test_control ( ) 인터페이스는 내부 의 읽기 에 사용되는
** 상태 SQLite 와 테스트 를 위해 SQLite 에 장애를 주입 하기 위해
** 목적. ^ 최초의 파라미터는 결정 작업 코드 이다
** 모든 후속 매개 변수 의 수, 의미 ​​, 운영 .
**
** 이 인터페이스는 응용 프로그램에서 사용 하기 위해서가 아닙니다. 그것은 단순히 존재하는
** SQLite 라이브러리 의 올바른 동작을 검증 하기 위하여. 따라
** SQLite 라이브러리를 컴파일 하는 방법은 이 인터페이스는 존재하지 않을 수 있습니다.
**
** 오퍼레이션 코드 , 의미 매개 변수 에 대한 자세한
** 그들은 가지고, 그들이 무슨 일을 하는지 는 사전 예고없이 변경 될 수 있습니다.
** SQLite 의 API 의 대부분 과 달리 이 기능은 보증 되지 않습니다
** 다음 1 릴리스 에서 일관되게 작동합니다.
* /
SQLITE_API int sqlite3_test_control(int op, ...);

/ * 
** CAPI3REF : 테스트 인터페이스 작동 코드 
** 
**이 상수는 사용되는 유효한 오퍼레이션 코드 매개 변수입니다 
** [sqlite3_test_control ()의 첫 번째 인수로. 
** 
**이 매개 변수와 그 의미는 변경 될 수 있습니다 
** 예고없이. 이러한 값은 테스트 목적만을위한 것입니다. 
** 응용 프로그램은 이러한 매개 변수 중 하나 또는 사용하여 안됩니다 
** [sqlite3_test_control () 인터페이스. 
* /
#define SQLITE_TESTCTRL_FIRST                    5
#define SQLITE_TESTCTRL_PRNG_SAVE                5
#define SQLITE_TESTCTRL_PRNG_RESTORE             6
#define SQLITE_TESTCTRL_PRNG_RESET               7
#define SQLITE_TESTCTRL_BITVEC_TEST              8
#define SQLITE_TESTCTRL_FAULT_INSTALL            9
#define SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS     10
#define SQLITE_TESTCTRL_PENDING_BYTE            11
#define SQLITE_TESTCTRL_ASSERT                  12
#define SQLITE_TESTCTRL_ALWAYS                  13
#define SQLITE_TESTCTRL_RESERVE                 14
#define SQLITE_TESTCTRL_OPTIMIZATIONS           15
#define SQLITE_TESTCTRL_ISKEYWORD               16
#define SQLITE_TESTCTRL_SCRATCHMALLOC           17
#define SQLITE_TESTCTRL_LOCALTIME_FAULT         18
#define SQLITE_TESTCTRL_EXPLAIN_STMT            19
#define SQLITE_TESTCTRL_NEVER_CORRUPT           20
#define SQLITE_TESTCTRL_LAST                    20

/ *
** CAPI3REF : SQLite 의 런타임 상태
**
** ^ 이 인터페이스는 런타임 상태 정보를 검색 하는 데 사용 되는
** SQLite는 성능 에 필요한 다양한 리셋
** 하이 워터 마크 . ^ 첫번째 인수는 정수 코드
** 측정 하는 특정 매개 변수입니다. ^ ( 인식 정수 코드
** 폼 상태 매개 변수 | SQLITE_STATUS_ ... ] 이다. ) ^
** ^ 매개 변수의 현재 값은 * pCurrent 에 되돌려진다.
** ^ 최고 기록 된 값은 * pHighwater 에 반환됩니다. ^ 만약
** resetFlag 가 true 의 경우 사상 최고치를 후 리셋 되는
*** pHighwater 이 적혀 있습니다. ^ ( 일부 매개 변수는 최고를 기록 하지
** 값 . 이러한 매개 변수 에 대한
** 아무것도 * pHighwater 에 쓰여지지 않고 resetFlag 는 무시 됩니다. ) ^
** ^ ( 다른 매개 변수는 레코드 만 하이 워터 마크 아니요 현재
** 값 . 이러한 후자 의 매개 변수 에 아무것도 * 의 pCurrent 에 기록되지 않습니다. ) ^
**
** ^ sqlite3_status ( ) 가 반환 성공을 SQLITE_OK 과
** 제로가 아닌 [ 오류 코드 ] 실패한 경우 .
**
** 이 루틴은 thread 세이프입니다 만 원자 는 없습니다. 이 루틴은 할 수 있습니다
다른 스레드 가 동일하거나 다른 SQLite 를 실행하는 동안 ** 라는
** 인터페이스. 그러나 값이 * 의 pCurrent 에 반환되고
*** pHighwater 다른 시점에서 의 SQLite 의 상태를 반영
**, 그것은 다른 스레드 에 매개 변수가 변경 될 가능성이 있을 수 있습니다
** 시간 동안 * pCurrent 과 * pHighwater 가 기록 될 때 .
**
** 참조 : [ sqlite3_db_status 을 ( )
* /
SQLITE_API int sqlite3_status(int op, int *pCurrent, int *pHighwater, int resetFlag);


/ *
** CAPI3REF : 상태 매개 변수
** KEYWORDS : { 상태 매개 변수 }
**
**이 정수 상수는 다양한 런타임 상태 매개 변수
** 그것이 반환 할 수 있습니다 [ sqlite3_status ( ) .
**
** <DL>
** [ SQLITE_STATUS_MEMORY_USED ] ^ ( <DT> SQLITE_STATUS_MEMORY_USED < / DT >
** <DD> 이 매개 변수는 현재 메모리 용량이 체크 아웃 된
** 직접 또는 간접적으로 [ ( ) sqlite3_malloc 를 사용. 더
** 그림은 응용 프로그램 [ sqlite3_malloc ( ) 에 추가 한 통화가 포함됩니다
** 와 SQLite 라이브러리 의 내부 메모리 사용 . 스크래치 메모리
** [ SQLITE_CONFIG_SCRATCH 및 보조 페이지 캐시 에 의해 제어
** [ SQLITE_CONFIG_PAGECACHE ] 에 의해 제어되는 메모리 는 포함 되지 않습니다
** 이 매개 변수입니다. 반환되는 금액은 할당 의 합계입니다
** [ sqlite3_mem_methods 에서 . < / DD > XSIZE 법 에 의해보고 된 크기 ) ^
**
** [ SQLITE_STATUS_MALLOC_SIZE ] ^ ( <DT> SQLITE_STATUS_MALLOC_SIZE < / DT >
** <DD> 이 매개 변수는 최대 메모리 할당 요청을 기록
** [ sqlite3_malloc ( ) 또는 sqlite3_realloc ( ) ( 또는 안겨준 그
** 내부 동등 ) . 유일한 값으로 반환
*** [ sqlite3_status ( ) 에 pHighwater 매개 변수가 중요하다.
*** pCurrent 매개 변수 에 기록 된 값이 정의 되어 있지 않습니다. < / DD > ) ^
**
** [ SQLITE_STATUS_MALLOC_COUNT ] ^ ( <DT> SQLITE_STATUS_MALLOC_COUNT < / DT >
** <DD> 이 매개 변수는 별도의 메모리 할당 수를 기록
** 현재 체크 아웃 . < / DD > ) ^
**
** [ SQLITE_STATUS_PAGECACHE_USED ] ^ ( <DT> SQLITE_STATUS_PAGECACHE_USED < / DT >
** <DD> 이 매개 변수는 외부 에 사용 된 페이지 수를 반환합니다.
** [ 페이지 캐시 메모리 할당 을 사용하여 설정 되었는지
** [ SQLITE_CONFIG_PAGECACHE ] . 더
** 반환되는 값은 페이지 의 바이트 는 아니고 이다. < / DD > ) ^
**
** [ SQLITE_STATUS_PAGECACHE_OVERFLOW ]
** ^ ( <DT> SQLITE_STATUS_PAGECACHE_OVERFLOW < / DT >
** <DD> 이 매개 변수는 페이지 캐시 의 바이트 수를 돌려줍니다
** [ SQLITE_CONFIG_PAGECACHE ] 를 만날 수 없었다 배급
** 버퍼 어디 가 sqlite3_malloc ( ) 의 오버 플로우를 피할 수 없게 되었다. 더
** 반환 값이 오버플로 의 매핑이 포함 되어 있기 때문에 이러한
** 여기 에서 ( 그들은 " 확인 " 매개 변수 보다 컸지 만 너무 커서
** [ SQLITE_CONFIG_PAGECACHE ] ) 과 오버플로 하고 있기 때문에 배급
** 에 공백이 페이지 캐시에 남아 있었다. < / DD > ) ^
**
** [ SQLITE_STATUS_PAGECACHE_SIZE ] ^ ( <DT> SQLITE_STATUS_PAGECACHE_SIZE < / DT >
** <DD> 이 매개 변수는 최대 메모리 할당 요청을 기록
** [ 페이지 캐시 메모리 할당 으로 전달했다. 유일한 값으로 반환
*** [ sqlite3_status ( ) 에 pHighwater 매개 변수가 중요하다.
*** pCurrent 매개 변수 에 기록 된 값이 정의 되어 있지 않습니다. < / DD > ) ^
**
** [ SQLITE_STATUS_SCRATCH_USED ] ^ ( <DT> SQLITE_STATUS_SCRATCH_USED < / DT >
** <DD> 이 매개 변수는 외부 에 사용되는 할당 수를 반환합니다.
** 스크래치 메모리 할당 ] 사용하여 설정
** [ SQLITE_CONFIG_SCRATCH ] . 반환되는 값은 할당되지 않은
** ( 바이트 ) . 하나의 스레드는 하나 의 스크래치 할당 이있는 경우가 있으므로
** 뛰어난 때이 매개 변수는 스레드 의 수를 보고합니다
** 동시에 스크래치 메모리 를 사용 하였다. < / 닫기 > ) ^
**
** [ SQLITE_STATUS_SCRATCH_OVERFLOW ] ^ ( <DT> SQLITE_STATUS_SCRATCH_OVERFLOW < / DT >
** <DD> 이 매개 변수는 스크래치 메모리 의 바이트 수를 돌려줍니다
** [ SQLITE_CONFIG_SCRATCH ] 를 만날 수 없었다 배급
** 버퍼 어디 가 sqlite3_malloc ( ) 의 오버 플로우를 피할 수 없게 되었다. 값
요구 된 할당 이 너무 이었기 때문에 ** 오버플 포함 반환
요구 된 할당 이 더 컸기 때문에 ** 큰 (즉,
** " 확인 " 매개 변수 [ SQLITE_CONFIG_SCRATCH ] )없이 스크래치 버퍼 를위한
** 슬롯을 사용할 수 있었다 .
** < / DD > ) ^
**
** [ SQLITE_STATUS_SCRATCH_SIZE ] ^ ( <DT> SQLITE_STATUS_SCRATCH_SIZE < / DT >
** <DD> 이 매개 변수는 최대 메모리 할당 요청을 기록
** 스크래치 메모리 할당 으로 전달했다. 유일한 값으로 반환
*** [ sqlite3_status ( ) 에 pHighwater 매개 변수가 중요하다.
*** pCurrent 매개 변수 에 기록 된 값이 정의 되어 있지 않습니다. < / DD > ) ^
**
** [ SQLITE_STATUS_PARSER_STACK ] ^ ( <DT> SQLITE_STATUS_PARSER_STACK < / DT >
** <DD> 이 매개 변수는 가장 깊은 파서 스택 을 기록합니다. 그것뿐입니다 .
** 의미있는 SQLite 는 [ YYTRACKMAXSTACKDEPTH 에서 . < / DD > ) ^ 컴파일 된 경우
** < / DL >
**
** 새로운 상태 매개 변수는 때 첨가해도 좋다.
* /
#define SQLITE_STATUS_MEMORY_USED          0
#define SQLITE_STATUS_PAGECACHE_USED       1
#define SQLITE_STATUS_PAGECACHE_OVERFLOW   2
#define SQLITE_STATUS_SCRATCH_USED         3
#define SQLITE_STATUS_SCRATCH_OVERFLOW     4
#define SQLITE_STATUS_MALLOC_SIZE          5
#define SQLITE_STATUS_PARSER_STACK         6
#define SQLITE_STATUS_PAGECACHE_SIZE       7
#define SQLITE_STATUS_SCRATCH_SIZE         8
#define SQLITE_STATUS_MALLOC_COUNT         9

/ * 
** CAPI3REF : 데이터베이스 연결 상태 
** 
** ^이 인터페이스는 런타임 상태 정보를 검색하는 데 사용되는 
** 단일 데이터베이스 연결에 대해. ^ 첫 번째 인수는있다 
** 데이터베이스 연결 개체를 확인할 수 있습니다. ^ 둘째 인수 
** 세트에서 가져온 정수이며, 
** [SQLITE_DBSTATUS 옵션 그 
** 심문하는 매개 변수를 결정합니다. 일련의 
** [SQLITE_DBSTATUS 옵션 그렇습니다 
** SQLite는 향후 릴리스에서 증식한다. 
** 
** ^ 요청 된 매개 변수의 현재 값은 * PCUR에 기록 된 
** 가장 높은 순간 값 * pHiwtr에 기록된다. ^ 만약 
** resetFlg가 true의 경우 최대 순간입니다 
** 현재 원래대로 돌려 놓으 재설정. 
** 
** ^ sqlite3_db_status ()가 반환 성공을 SQLITE_OK과 
** 제로가 아닌 [오류 코드] 실패한 경우. 
** 
** 참조 : [sqlite3_status () 및 sqlite3_stmt_status (). 
* / 
SQLITE_API int sqlite3_db_status(sqlite3*, int op, int *pCur, int *pHiwtr, int resetFlg);

/ * 
** CAPI3REF : 데이터베이스 연결 상태 매개 변수 
** KEYWORDS : {SQLITE_DBSTATUS 옵션} 
** 
**이 상수는로 전달할 수있는 사용 가능한 정수 "동사"이다 
** [sqlite3_db_status () 인터페이스의 두 번째 인수. 
** 
** 새로운 동사는 SQLite는 이후 릴리스에서 추가 할 수있다. 기존 동사 
** 중단 될 수 있습니다. 응용 프로그램에서의 리턴 코드를 확인해야합니다 
** [sqlite3_db_status () 호출이 일하던 확인한다. 
** [sqlite3_db_status () 인터페이스는 아닌 에러 코드를 반환합니다. 
** 중단되거나 지원되지 않는 동사가 불려 갔을 경우. 
** 
** <DL> 
** [SQLITE_DBSTATUS_LOOKASIDE_USED] ^ (<DT> SQLITE_DBSTATUS_LOOKASIDE_USED </ DT> 
** <DD>이 매개 변수는 현재 룩 어 사이드 메모리 슬롯의 수를 돌려줍니다. 
** 체크 아웃했다. </ DD>) ^ 
** 
** [SQLITE_DBSTATUS_LOOKASIDE_HIT] ^ (<DT> SQLITE_DBSTATUS_LOOKASIDE_HIT </ DT> 
** <DD>이 매개 변수는 없었다 숫자 malloc 시도를 반환 
** 룩 어 사이드 메모리를 사용하여 만족했다. 오직 높은 물 값은 의미가 있습니다. 
** 현재 값은 항상 0입니다. ) ^ 
** 
** [SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE] 
** ^ (<DT> SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE </ DT> 
** <DD>이 매개 변수는 가지고 있을지도 모른다 숫자 malloc 시도를 반환 
** 룩 어 사이드 메모리를 사용하여 만족하지만위한 양 실패 
** 메모리 고개-aside 슬롯 크기보다 큰 요청되었다. 
** 유일한 만조 값은 의미가 있습니다. 
** 현재 값은 항상 0입니다. ) ^ 
** 
** [SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL] 
** ^ (<DT> SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL </ DT> 
** <DD>이 매개 변수는 가지고 있을지도 모른다 숫자 malloc 시도를 반환 
** 룩 어 사이드 메모리를 사용하여 만족하고 있습니다 만 내리는 룩 어 사이드에 실패한 
** 이미 사용 된 메모리. 
** 유일한 만조 값은 의미가 있습니다. 
** 현재 값은 항상 0입니다. ) ^ 
** 
** [SQLITE_DBSTATUS_CACHE_USED] ^ (<DT> SQLITE_DBSTATUS_CACHE_USED </ DT> 
** <DD>이 매개 변수는 힙의 바이트의 대략적인 수를 돌려줍니다 
** 데이터베이스 연결에 연결된 모든 호출기 캐시가 사용하는 메모리). ^ 
** ^ SQLITE_DBSTATUS_CACHE_USED에 대한 하이 워터 마크는 항상 0입니다. 
** 
** [SQLITE_DBSTATUS_SCHEMA_USED] ^ (<DT> SQLITE_DBSTATUS_SCHEMA_USED </ DT> 
** <DD>이 매개 변수는 힙의 바이트의 대략적인 수를 돌려줍니다 
** 메모리는 관련된 모든 데이터베이스 스키마를 저장하는 데 사용 
메인, TEMP 및 모든-ED 데이터베이스 첨부를) ^ - ^ ** 연결 
** ^ 스키마에 사용되는 메모리 전액을보고 있어도 
** 스키마 메모리를 위해 다른 데이터베이스 연결 및 공유 된 
** 공유 캐시 모드를 사용하고있다. 
** ^ SQLITE_DBSTATUS_SCHEMA_USED에 대한 하이 워터 마크는 항상 0입니다. 
** 
** [SQLITE_DBSTATUS_STMT_USED] ^ (<DT> SQLITE_DBSTATUS_STMT_USED </ DT> 
** <DD>이 매개 변수는 힙의 바이트의 대략적인 수를 돌려줍니다 
연결된 모든 준비 된 문장이 사용 ** 및 조회 아 사이드 메모리 
** 데이터베이스 연결). ^ 
** ^ SQLITE_DBSTATUS_STMT_USED에 대한 하이 워터 마크는 항상 0입니다. 
** </ DD> 
** 
** [SQLITE_DBSTATUS_CACHE_HIT] ^ (<DT> SQLITE_DBSTATUS_CACHE_HIT </ DT> 
** <DD>이 매개 변수는 가지고 호출기 캐시 적중 수를 돌려줍니다 
** 발생했습니다. ) ^ ^ SQLITE_DBSTATUS_CACHE_HIT에 대한 하이 워터 마크 
** 항상 0입니다. 
** </ DD> 
** 
** [SQLITE_DBSTATUS_CACHE_MISS] ^ (<DT> SQLITE_DBSTATUS_CACHE_MISS </ DT> 
** <DD>이 매개 변수는 가지고 호출기 캐시 미스의 수를 돌려줍니다 
** 발생했습니다. ) ^ ^ SQLITE_DBSTATUS_CACHE_MISS에 대한 하이 워터 마크 
** 항상 0입니다. 
** </ DD> 
** 
** [SQLITE_DBSTATUS_CACHE_WRITE] ^ (<DT> SQLITE_DBSTATUS_CACHE_WRITE </ DT> 
** <DD>이 매개 변수는 가지고 더티 캐시 항목의 수를 돌려줍니다 
** 디스크에 기록되었다. 구체적으로는 페이지에 기록 
**의 WAL WAL 모드 데이터베이스 파일 또는 쓰기 페이지 수 
** 롤백 모드 데이터베이스의 데이터베이스 파일입니다. 의 일부로 작성된 모든 페이지 
** 트랜잭션 롤백이나 데이터베이스의 복구 작업이 포함되어 있지 않습니다. 
** 디스크에 페이지의 기입 중에 입출력 또는 기타 오류가 발생한 경우 효과는 
** 후속 SQLITE_DBSTATUS_CACHE_WRITE 요청에 정의되어 있지 않습니다. ) ^ ^ 
SQLITE_DBSTATUS_CACHE_WRITE에 연결된 ** 하이 워터 마크는 항상 0입니다. 
** </ DD> 
** 
** [SQLITE_DBSTATUS_DEFERRED_FKS] ^ (<DT> SQLITE_DBSTATUS_DEFERRED_FKS </ DT> 
** <DD>이 매개 변수는 현재 값에 0을 돌려주는 경우에 한정 
** 모든 외래 키 제약 조건 (연기 또는 즉시)가 된 
** 해결했습니다. ) ^ ^ 하이 워터 마크는 항상 0입니다. 
** </ DD> 
** </ DL> 
* /
#define SQLITE_DBSTATUS_LOOKASIDE_USED       0
#define SQLITE_DBSTATUS_CACHE_USED           1
#define SQLITE_DBSTATUS_SCHEMA_USED          2
#define SQLITE_DBSTATUS_STMT_USED            3
#define SQLITE_DBSTATUS_LOOKASIDE_HIT        4
#define SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE  5
#define SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL  6
#define SQLITE_DBSTATUS_CACHE_HIT            7
#define SQLITE_DBSTATUS_CACHE_MISS           8
#define SQLITE_DBSTATUS_CACHE_WRITE          9
#define SQLITE_DBSTATUS_DEFERRED_FKS        10
#define SQLITE_DBSTATUS_MAX                 10   /* Largest defined DBSTATUS */


/ * 
** CAPI3REF : 준비된 문 상태 
** 
** ^ (각 준비된 문은 다양한 유지 
수를 측정 ** [SQLITE_STMTSTATUS 카운터] 
** 시대의 그것은 특정 작업을 수행했습니다. ) ^이 카운터는 할 수 있습니다 
** 조제의 성능 특성을 모니터링하는 데 사용할 수 
** 문장. 예를 들어 테이블의 단계 수를 크게 초과하는 경우 
** 테이블을 검색 또는 결과 행의 수는 그것이 나타내는 경향이있다 
** 준비된 문장이 전체 테이블 스캔을 사용하여 것이 아니라되는 것 
** 인덱스. 
** 
** ^ (이 인터페이스는에서 카운터 값을 가져 재설정하는 데 사용되는 
** [준비된 문]. 첫 번째 인수는 준비된 문이다 
** 개체가 심문된다. 둘째 인수 
** 특정의 SQLITE_STMTSTATUS 카운터에 정수 코드 
** 심문한다. ) ^ 
** ^ 요청한 카운터의 현재 값을 반환합니다. 
** ^ resetFlg가 true의 경우, 카운터는이 후 0으로 재설정된다 
** 인터페이스의 호출로 돌아갑니다. 
** 
** 참조 : [sqlite3_status () 및 sqlite3_db_status (). 
* /
SQLITE_API int sqlite3_stmt_status(sqlite3_stmt*, int op,int resetFlg);

/ * 
** CAPI3REF : 준비된 문 상태 매개 변수 
** KEYWORDS : {SQLITE_STMTSTATUS 카운터} {SQLITE_STMTSTATUS 카운터} 
** 
**이 전 처리기 매크로는 카운터에 이름을 정수 코드를 정의하는 
** [sqlite3_stmt_status () 인터페이스에 관련 지을 수 있었던 값. 
다음과 같이 ** 각종 카운터의 의미는 다음과 같습니다. 
** 
** <DL> 
** [SQLITE_STMTSTATUS_FULLSCAN_STEP] <DT> SQLITE_STMTSTATUS_FULLSCAN_STEP </ DT> 
** <DD> ^ 이것은 SQLite가 나와 앞으로왔다 횟수 
** 풀 테이블 스캔의 일부로 테이블. 이 카운터의 많은 
**을 통해 성능 향상을위한 기회를 의미 할 수도 
** 지표를주의 깊게 사용. </ DD> 
** 
** [SQLITE_STMTSTATUS_SORT] <DT> SQLITE_STMTSTATUS_SORT </ DT> 
** <DD> ^이 발생한 정렬 작업의 수입니다. 
**이 카운터의 0이 아닌 값은하는 기회를 나타낼 수 있습니다 
** 지표를주의 깊게 사용하여 개선 성능. </ DD> 
** 
** [SQLITE_STMTSTATUS_AUTOINDEX] <DT> SQLITE_STMTSTATUS_AUTOINDEX </ DT> 
** <DD> ^ 이것은 임시 인덱스에 삽입 된 행의 수가있다 
** 빠르게 실행 조인 할 수 있도록 자동으로 작성되었다. 
**이 카운터의 0이 아닌 값은하는 기회를 나타낼 수 있습니다 
없는 영구적 인 지표를 추가하여 ** 개선 성능 
** 문이 실행될 때마다 다시 초기화해야합니다. </ DD> 
** 
** [SQLITE_STMTSTATUS_VM_STEP] <DT> SQLITE_STMTSTATUS_VM_STEP </ DT> 
** <DD> ^ 가상 컴퓨터의 작업 수는이 실행되는 
** 조제 문장에 의해 그 수가 이하인 경우 
** 2147483647까지. 가상 컴퓨터 작업의 수와 수 
** 준비된 문에 의해 수행, 모든 작업을위한 프록시로 사용. 
** 가상 머신의 작업 수가 2147483647를 초과하는 경우 
**이 글의 상태 코드로 반환되는 값은 부정입니다. 
** </ DD> 
** </ DL> 
* /
#define SQLITE_STMTSTATUS_FULLSCAN_STEP     1
#define SQLITE_STMTSTATUS_SORT              2
#define SQLITE_STMTSTATUS_AUTOINDEX         3
#define SQLITE_STMTSTATUS_VM_STEP           4

/ * 
** CAPI3REF : 사용자 지정 페이지 캐시 개체 
** 
** sqlite3_pcache 유형은 불투명하다. 이것은 의해 실현되는 
** 플러 거블 모듈. SQLite의 핵심은 지식이 없습니다. 
** 결코 그 크기와 내부 구조와 취급 
포인터를 포함하여 전달하여 제외한 ** sqlite3_pcache 개체 
** 개체에. 
** 
** 자세한 내용은 [sqlite3_pcache_methods2를 참조하십시오. 
* /
typedef struct sqlite3_pcache sqlite3_pcache;

/ * 
** CAPI3REF : 사용자 지정 페이지 캐시 개체 
** 
** sqlite3_pcache_page 개체는 단일 페이지를 나타냅니다 
** 페이지 캐시. 페이지 캐시는이 인스턴스에 할당합니다 
** 개체입니다. 인스턴스의 페이지 캐시 사용 포인터의 다양한 방법 
**이 개체의 매개 변수 또는 반환 값으로. 
** 
** 자세한 내용은 [sqlite3_pcache_methods2를 참조하십시오. 
* /
typedef struct sqlite3_pcache_page sqlite3_pcache_page;
struct sqlite3_pcache_page {
  void *pBuf;        /* The content of the page */
  void *pExtra;      /* Extra information associated with the page */
};

/ * 
** CAPI3REF : 응용 프로그램 페이지 캐시를 정의했습니다. 
** KEYWORDS : {페이지 캐시} 
** 
** ^ (sqlite3_config] (SQLITE_CONFIG_PCACHE2, ...) CAN 인터페이스 
**를 전달하여 대체 페이지 캐시의 구현을 등록하는 
** sqlite3_pcache_methods2 구조체의 인스턴스. ) ^ 
** 많은 응용 프로그램은 힙 메모리의 대부분에 의해 할당 된 
** SQLite는 페이지 캐시에 사용됩니다. 
** 구현하여 
**이 API를 사용하여 사용자 정의 페이지 캐시는 응용 프로그램이 제어를 향상 할 수 있습니다 
SQLite의 방법에 의해 소비되는 메모리 양입니다. ** 
** 메모리가 할당 해제 된 정책이 사용되는 
** 결정하고 정확하게 데이터베이스 파일의 일부가 캐시되어 있다고하는 
** 얼마나. 
** 
** 대체 페이지 캐싱 메커니즘이다 
유일한 가장 까다로운 어플리케이션에서 필요로되고있다. ** 극단적 인 조치. 
** 내장의 페이지 캐시는 대부분의 용도에 권장됩니다. 
** 
** ^ (sqlite3_pcache_methods2 구조체의 내용을 복사하는 
** [sqlite3_config] 호출의 SQLite의 내부 버퍼. 그러므로 
** 응용 프로그램은 호출 후 파라미터를 파기 할 수있다 
** [sqlite3_config ()]로 돌아갑니다. ) ^ 
** 
** [XINIT () 페이지 캐시 방법] 
** ^ (XINIT () 메서드는 각 활성화 한 번 불리고 
** ^ [sqlite3_initialize ())의 호출 
** (일반적으로 한 번만 프로세스의 수명 동안). ^ (XINIT () 
** 메서드는 sqlite3_pcache_methods2.pArg 값의 복사본이 전달됩니다.) ^ 
**의 xinit () 메서드의 목적은 글로벌 데이터 구조를 설정하는 것입니다 
** 사용자 지정 페이지 캐시 구현에 의해 요구된다. 
** ^ (XINIT () 메서드가 NULL의 경우, 
** 내장 된 기본 페이지 캐시 대신 정의 된 응용 프로그램의 사용 된 
** 페이지 캐시). ^ 
** 
** [xShutdown () 페이지 캐시 방법] 
** ^ xShutdown () 메서드에서 sqlite3_shutdown ()에 의해 호출됩니다. 
** 이것은 정리하는 데 사용할 수 있습니다 
** 처리되지 않은 자원의 프로세스가 종료하기 전에 필요한 경우. 
** ^ xShutdown () 메서드는 NULL을 지정할 수 있습니다. 
** 
** ^ SQLite는 자동으로 xinit 메서드 호출을 직렬화하고 
** 때문에, xinit 메서드가 스레드로부터 안전 할 필요는 없습니다. ^ 
** xShutdown 방법은 [sqlite3_shutdown ()에서 호출되므로 그것은 아닙니다 된 
** 어느 스레드로부터 안전 필요하지. 다른 모든 메소드는 thread 세이프가 아니면 안됩니다 
** 다중 스레드 응용 프로그램. 
** 
** ^ SQLite는 개입하지 않고 여러 번) 더 (XINIT를 호출하지 않습니다 
**) (xShutdown 호출합니다. 
** 
** [xCreate () 페이지 캐시 방법] 
** ^ SQLite는 새로운 캐시 인스턴스를 구성하는 데 xCreate () 메서드를 호출합니다. 
** SQLite는 일반적으로 각 데이터베이스 파일의 오픈을 위해 1 캐시 인스턴스를 만들지 만,
**이 보장되는 것은 아니다. ^ 
** 첫 번째 매개 변수 szPage는 그 필요가있는 페이지의 크기 (바이트)입니다. 
** 캐시가 할당된다. ^ szPage 항상 두 개의 힘을합니다. ^ 
** 번째 매개 변수 szExtra 여분의 스토리지 바이트이다 
** 각 페이지의 캐시 엔트리에 연결된. ^ szExtra 매개 변수는됩니다 
** 250 미만의 수입니다. SQLite는 사용됩니다 
** 여분 szExtra는 기본 메타 데이터를 저장하기 위해 각 페이지의 바이트 
디스크의 ** 데이터베이스 페이지. szExtra에 전달되는 값은 다릅니다 
** SQLite 버전 대상 플랫폼 및 어떻게 SQLite를 컴파일되었습니다. 
캐시가있는 경우 ** ^ xCreate () bPurgeable 세 번째 인수가 참이다 
** 디스크에 저장되어있는 파일의 데이터베이스 페이지를 캐시하기 위해 만들어 사용되거나 
** 그것은 인 메모리 데이터베이스에 사용되고있는 경우는 false입니다. 캐시 구현 
** bPurgeable의 값에 따라 특별한 것을 할 필요가 없습니다. 
** 그것은 순전히 고문입니다. ^ bPurgeable 가짜 캐시에서 SQLite까요 
** 고의로 페이지를 삭제하는 것 외에 xUnpin ()를 호출하지 않습니다. 
** ^ 즉, 설정 bPurgeable 캐시에서) (xUnpin 호출 
** 허위은 항상 true로 설정된 "폐기"플래그를 갖게됩니다. 
** ^ 따라서 캐시가 bPurgeable 허위의 의지를 사용하여 작성 
** 모든 고정 해제 페이지가 포함 된 것은 아닙니다. 
** 
** [xCachesize () 페이지 캐시 방법] 
** ^ (xCachesize () 메서드는 설정하기 위해서 SQLite는 것으로, 언제라도 호출 할 수 있습니다 
** 제안 캐시의 최대 크기 (에 의해 저장된 페이지) 캐시 
** 인스턴스는 첫 번째 인수로 전달된다. 이것은 사용하여 구성된 값이다 
** SQLite는 "[프라 그마 CACHE_SIZE]"명령을 사용합니다. ) ^ bPurgeable와 마찬가지로 
** 매개 변수는 구현은 이제 아무것도 할 필요가 없습니다 
** 값, 그것이 유일한 지도자이다. 
** 
** [xPagecount () 페이지 캐시 방법] 
** xPagecount () 메서드는 현재의 페이지 수를 반환해야합니다 
** 모두 핀과 핀 해제 캐시에 저장되어있다. 
** 
** [xFetch () 페이지 캐시 방법] 
** xFetch () 메서드는 캐시의 페이지를 찾아 내고 몸에 대한 포인터를 반환 
** 해당 페이지에 연결된 sqlite3_pcache_page 개체 또는 NULL 포인터. 
** 반환 sqlite3_pcache_page 개체의 PBUF 요소가됩니다 
**의 내용을 저장하는 데 사용 szPage 바이트의 버퍼 포인터 
** 단일 데이터베이스 페이지. sqlite3_pcache_page의 pExtra 요소가됩니다 
** SQLite가 요구 한 추가 기억 szExtra 바이트에 대한 포인터 
** 페이지 캐시의 각 항목. 
** 
** 페치되는 페이지는 키에 의해 결정된다. ^ 최소의 키 값 
** 1입니다. 그것은 xFetch를 사용하여 검색 한 후 페이지가 간주됩니다 
** '고정'된다. 
** 
** 요청한 페이지가 페이지 캐시에 이미 존재하는 경우는 페이지 캐시 
** 구현은 그 내용의 페이지 버퍼에 대한 포인터를 반환해야합니다 
** 그대로. 요청한 페이지는 캐시에 존재하지 않는 경우 
** 캐쉬는 createFlag 값을 사용해야합니다 
** 그것이 수행 할 작업을 결정하는 데 도움이 파라미터 : 
** 
** <table border=1 width=85% al​​ ign=center> 
** <TR> 번째 createFlag 번째 동작시 페이지가 캐시에 존재하지 않는 
** <TR> <TD> 0 <TD> 새 페이지를 할당하지 마십시오. NULL을 돌려 준다. 
그것은 간단하고 유용하게하려면 ** <TR> <TD> 1 <TD> 새 페이지를 할당합니다. 
** 그렇지 않은 경우는 null를 돌려줍니다. 
** <TR> <TD> 2 <TD> 새로운 페이지를 할당하기 위해 모든 노력을한다. 유일한 반환 
** NULL 새 페이지를 할당 할 사실상 불가능한 경우. 
** </ 테이블> 
** 
** ^ (SQLite는 일반적으로 0 또는 1의 createFlag에서 xFetch ()를 호출합니다. SQLite의 
** 만 1 createFlag와 사전 호출 후 2 createFlag을 사용합니다 
** 실패했습니다. ) ^에서 xFetch에 () 사이에서 SQLite는 가능성을 호출 
**의 내용을 흘리고, 하나 이상의 캐시 페이지를 분리하려고 시도 
** 페이지를 디스크에 고정 된 운영 체제의 디스크 캐시를 박. 
** 
** [xUnpin () 페이지 캐시 방법] 
** ^ xUnpin ()는 현재 고정 페이지 포인터에서 SQLite에 의해 불려갑니다 
** 둘째 인수로. 세 번째 매개 변수는 소멸 한 경우, 제로가 아닌 
** 페이지는 캐시에서 제거되어야한다. 
** ^ 폐기 매개 변수 인 경우 
** 제로 페이지가 삭제 또는 재량으로 유지 될 수있다 
** 페이지 캐시 구현. ^ 페이지 캐시 구현 
** 언제든지 고정 해제 페이지를 삭제하려면 선택 할 수 있습니다. 
** 
** 캐시는 임의의 참조 카운트를 실행해서는 안된다. 싱글 
** xUnpin ()의 호출에 관계없이 이전 통화의 페이지 잠금을 해제합니다 
** xFetch에 (). 
** 
** [xRekey () 페이지 캐시 방법] 
** xRekey () 메서드는 연결된 키 값을 변경하는 데 사용되는 
** 페이지에는 두 번째 인수로 전달된다. 경우 캐시 
** 이전 NEWKEY에서 관련 항목을 포함하고 그게 없으면 안됩니다 
** 파기. ^ NEWKEY에 연결된 사전 캐시 엔트리가없는 것이 보증된다 
** 달아 할 수있다. 
** 
SQLite는 xTruncate () 메서드를 호출하면 ** 캐시는 모두 파기해야합니다 
이상의 페이지 번호 (키)을 가지는 ** 기존 캐시 엔트리 
** xTruncate (전달 ILIMIT 매개 변수의 값까지). 있는 경우 
**이 페이지가 핀되고 그들은 즉 암시 적으로 해제되는 것을 
**이 안전하게 폐기 할 수있다. 
** 
** [xDestroy () 페이지 캐시 방법] 
** ^ xDestroy () 메서드는 xCreate ()에 의해 할당 된 캐시를 제거하기 위해 사용된다. 
** 지정된 캐시에 연결된 모든 리소스를 해제해야합니다. ^ 후 
** xDestroy () 메서드를 호출하여 SQLite는 [sqlite3_pcache *를 생각 
** 잘못된 핸들 및 기타 sqlite3_pcache_methods2와 함께 사용할 수 없습니다. 
** 기능. 
** 
** [xShrink () 페이지 캐시 방법] 
그것은 페이지 캐시를하고 싶을 때 ** ^ SQLite는 xShrink () 메서드를 호출합니다 
** 가능한 힙 메모리를 가능한 한 많이 풀어. 페이지 캐시 구현 
** 메모리를 해제 할 의무가 있지만, 제대로 작동하는 구현은 아닐거야 
** 최선을 다해. 
* /
typedef struct sqlite3_pcache_methods2 sqlite3_pcache_methods2;
struct sqlite3_pcache_methods2 {
  int iVersion;
  void *pArg;
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  sqlite3_pcache *(*xCreate)(int szPage, int szExtra, int bPurgeable);
  void (*xCachesize)(sqlite3_pcache*, int nCachesize);
  int (*xPagecount)(sqlite3_pcache*);
  sqlite3_pcache_page *(*xFetch)(sqlite3_pcache*, unsigned key, int createFlag);
  void (*xUnpin)(sqlite3_pcache*, sqlite3_pcache_page*, int discard);
  void (*xRekey)(sqlite3_pcache*, sqlite3_pcache_page*, 
      unsigned oldKey, unsigned newKey);
  void (*xTruncate)(sqlite3_pcache*, unsigned iLimit);
  void (*xDestroy)(sqlite3_pcache*);
  void (*xShrink)(sqlite3_pcache*);
};

/ * 
** 이것은 지금 교체 한 구식 pcache_methods 개체입니다 
** sqlite3_pcache_methods2에 따른다. 이 개체는 SQLite 것이 사용되지 않습니다. 그것은 
** 만 호환성을위한 헤더 파일에 보관. 
* /
typedef struct sqlite3_pcache_methods sqlite3_pcache_methods;
struct sqlite3_pcache_methods {
  void *pArg;
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  sqlite3_pcache *(*xCreate)(int szPage, int bPurgeable);
  void (*xCachesize)(sqlite3_pcache*, int nCachesize);
  int (*xPagecount)(sqlite3_pcache*);
  void *(*xFetch)(sqlite3_pcache*, unsigned key, int createFlag);
  void (*xUnpin)(sqlite3_pcache*, void*, int discard);
  void (*xRekey)(sqlite3_pcache*, void*, unsigned oldKey, unsigned newKey);
  void (*xTruncate)(sqlite3_pcache*, unsigned iLimit);
  void (*xDestroy)(sqlite3_pcache*);
};


/ * 
** CAPI3REF : 온라인 백업 개체 
** 
** 전진하는 약 sqlite3_backup 개체 레코드 상태 정보 
** 온라인 백업 조작. ^ sqlite3_backup 개체는 다음과 같은 방법으로 생성 된 
** [sqlite3_backup_init ()에 대한 호출은 호출에 의해 파괴되는 
** [sqlite3_backup_finish (). 
** 
** 참고 항목 : SQLite는 온라인 백업 API를 사용하는] 
* /
typedef struct sqlite3_backup sqlite3_backup;

/ * 
** CAPI3REF : 온라인 백업 API. 
** 
** 백업 API의 복사 또 다른 한개에 1 데이터베이스의 내용. 
** 이것은 데이터베이스를 백업하는 중 하나에 편리합니다 
** 영구 파일 또는에서 인 메모리 데이터베이스를 복사하기 위하여. 
** 
** 참고 항목 : SQLite는 온라인 백업 API를 사용하는] 
** 
** ^ SQLite는 대상 데이터베이스 파일에 열려 쓰기 트랜잭션을 보유하고 
** 백업 작업 사이. 
** ^ 소스 데이터베이스는 읽기 잠겨 그것이로드되고있는 동안 만. 
** 그것이 전체 백업 작업을 위해 지속적으로 잠겨 있지 않습니다. 
** ^ 이처럼 백업이 없으면 살아 소스 데이터베이스에서 실행할 수있다 
** 다른 데이터베이스 연결을 방지 
** 백업이 진행되는 동안 소스 데이터베이스에 대한 읽기 또는 쓰기. 
** 
** ^ (백업 작업을 수행하려면 : 
** <OL> 
** <LI> <B> sqlite3_backup_init () </ B>을 초기화하기 위해 한 번만 호출 
** 백업, 
** <LI> <B> sqlite3_backup_step () </ B> 전송하기 위해 1 회 이상이라고하는 
결국 ** 개의 데이터베이스 간의 데이터 및 
** <LI> <B> sqlite3_backup_finish () </ B>는 모든 리소스를 해제하기 위해 호출되는 
** 백업 작업 관련. 
** </ OL>) ^ 
** 각각 sqlite3_backup_finish 정확히 1 통화 ()가 있어야합니다 
sqlite3_backup_init하는 ** 호출이 성공 (). 
** 
** [sqlite3_backup_init ()]] <B> sqlite3_backup_init () </ B> 
** 
** ^ D와 N의 인수 sqlite3_backup_init에 (D, N, S, M)가있다 
대상 데이터베이스에 대한 ** 데이터베이스 연결 
**과 데이터베이스 이름이었다. 
** ^ 데이터베이스 이름은 "주요"기본 데이터베이스를위한 "TEMP"입니다 
** 임시 데이터베이스 또는의 AS 키워드 다음에 지정된 이름 
연결된 데이터베이스에 대한 ** 첨부] 계산서. 
** ^ S와 M의 인수가 전달 된 
** sqlite3_backup_init (D, N, S, M)을 식별하고 데이터베이스 연결 
소스 데이터베이스의 **과 데이터베이스 이름이었다. 
** ^ 원본 및 대상 데이터베이스 연결 (매개 변수 s와 D) 
** (D, N, S, M)로 실패합니다 다른도해야 sqlite3_backup_init해야합니다 
** 오류. 
** 
오류 (D, N, S, M) sqlite3_backup_init에서 발생한 경우 ** ^ NULL이있는 
** 리턴 오류 코드 오류 메시지가 동안 기억되고있다 
** 대상 데이터베이스 연결 D. 
** ^ (sqlite3_backup_init에 실패한 호출 오류 코드 및 메시지) 
** [sqlite3_errcode (), sqlite3_errmsg () 및 / 또는을 사용하여 얻을 수 있습니다 
** [sqlite3_errmsg16 () 기능. 
** ^ sqlite3_backup_init에 대한 호출이 성공하면 ()에 대한 포인터를 반환 
** [sqlite3_backup 개체. 
** ^ [sqlite3_backup】 개체가 sqlite3_backup_step 함께 사용할 수있다 ()와 
지정된 백업을 수행하는 ** sqlite3_backup_finish () 함수 
** 조작. 
** 
** [sqlite3_backup_step ()]] <B> sqlite3_backup_step () </ B> 
** 
** ^ 기능 sqlite3_backup_step (B, N) 사이에 N 페이지까지 복사됩니다 
[sqlite3_backup 개체 B에서 지정된 ** 소스 및 대상 데이터베이스 
N가 부의 경우 ** ^ 나머지 모든 소스 페이지가 복사된다. 
거기 ** ^ 만약 sqlite3_backup_step (B, N)이 성공적으로 복사 N 페이지와 
** 복사하는 것은 아직도 많은 페이지가 있고이 함수는 [SQLITE_OK을 반환합니다. 
** ^ sqlite3_backup_step (B, N)이 성공적으로 모든 페이지를 복사하여 종료 된 경우 
** 소스에서 목적지까지 그것은 [SQLITE_DONE을 반환합니다. 
** ^ sqlite3_backup_step (B, N)를 실행하는 동안 오류가 발생한 경우 
** 다음 오류 코드를 반환합니다. ^뿐만 아니라 [SQLITE_OK 및 
** [SQLITE_DONE, sqlite3_backup_step ()를 호출하면 SQLITE_READONLY을 반환 할 수 있습니다 
** [SQLITE_NOMEM, SQLITE_BUSY, SQLITE_LOCKED 또는 
** [SQLITE_IOERR_ACCESS | SQLITE_IOERR_XXX] 확장 오류 코드입니다. 
** 
** ^ (sqlite3_backup_step () 반환 될 수 있습니다 [SQLITE_READONLY]의 경우 
** <OL> 
** <LI> 대상 데이터베이스는 읽기 전용으로 열린 또는 
** 대상 데이터베이스 <LI> 미리 쓰기 로그 저널링을 사용하고 있습니다 
** 및 대상과 원본의 페이지 크기가 다르거 나 
** 대상 데이터베이스 <LI> 인 메모리 데이터베이스이며, 
** 원본 및 대상의 페이지 크기가 다릅니다. 
** </ OL>) ^ 
** 
** ^ sqlite3_backup_step ()는 필요한 파일 시스템의 잠금을 얻을 수없는 경우 
** [sqlite3_busy_handler | 바쁜 핸들러 함수] 
(1이 지정된 경우) ** 시작됩니다. ^ 만약 
락이하여 사용할 수있게 전에 ** 바쁜 처리기 0이 아닌 반환 
** [SQLITE_BUSY]는 호출자에게 반환됩니다. ^이 경우 호출 
** sqlite3_backup_step () 나중에 다시 시도 할 수 있습니다. ^ 만약 소스 
** 데이터베이스 연결 
** sqlite3_backup_step 때 소스 데이터베이스에 쓰는 데 사용되는 () 
**라고되어 있으며, SQLITE_LOCKED]가 즉시 반환됩니다. ^ 다시 말하지만,이 중 
** 케이스는 sqlite3_backup_step ()를 호출하면 나중에 다시 시도 할 수 있습니다. ^ (만약
** [SQLITE_IOERR_ACCESS | SQLITE_IOERR_XXX, SQLITE_NOMEM 또는 
** [SQLITE_READONLY] 그런 다음 반환 
** 재시도 포인트 sqlite3_backup_step하는 ()의 호출이 없습니다. 이러한 
** 오류는 치명적인 것으로 간주됩니다. ) ^ 어플리케이션은 받아 들여야한다 
** 백업 작업이 실패하고 백업 작업 핸들을 전달했다는 것을 
** sqlite3_backup_finish에 ()와 연결된 리소스를 해제합니다. 
** 
** ^ sqlite3_backup_step의 최초의 호출 ()은 단독 잠금을 
** 대상 파일에. ^ 단독으로 잠길 때까지 해제되지 않습니다 
** sqlite3_backup_finish ()가 호출 된 백업 작업이 완료되었습니다 
**와 sqlite3_backup_step () [SQLITE_DONE을 반환합니다. ^에 대한 모든 호출 
** sqlite3_backup_step ()는 소스 데이터베이스에서 공유 잠금을 얻을 
** sqlite3_backup_step () 호출 동안 지속된다. 
** ^ 소스 데이터베이스는 호출 사이에 잠겨 있지 않기 때문에 
** sqlite3_backup_step ()는 소스 데이터베이스가 도중에 변경되어있다 
** 백업 프로세스를 통해. ^ 소스 데이터베이스에 의해 수정 된 경우 
** 외부 프로세스 또는 1 이외의 다른 데이터베이스 연결을 통해 
** 백업 작업에 사용 된 백업은 자동으로됩니다 
** ()을 sqlite3_backup_step의 다음의 호출에 의해 다시 시작합니다. ^ 만약 소스 
** 데이터베이스는 동일한 데이터베이스 연결을 사용하여 사용되는 것으로 규정되어있다 
** 백업하면 백업 데이터베이스가 자동으로 
** 동시에 갱신. 
** 
** [sqlite3_backup_finish ()]] <B> sqlite3_backup_finish () </ B> 
** 
** sqlite3_backup_step ()는 [SQLITE_DONE] 돌아온 때 또는 때 
** 응용 프로그램은 응용 프로그램 백업 작업을 포기하고 싶으면 
** [sqlite3_backup ()을 sqlite3_backup_finish에 전달하여 파괴해야합니다. 
** ^ sqlite3_backup_finish () 인터페이스를 모두 해제 
** [sqlite3_backup 개체에 연결된 자원. 
** ^ sqlite3_backup_step ()이 계속되고, SQLITE_DONE] 반환되지 않은 경우 
** 대상 데이터베이스의 활성 쓰기 트랜잭션이 롤백됩니다. 
** [sqlite3_backup 개체가 유효하지 않습니다 
**와 ()를 sqlite3_backup_finish 호출 후 사용할 수 없습니다. 
** 
** ^ sqlite3_backup_finish에 의해 반환되는 값은 SQLITE_OK]의 경우이 없습니다. 
** sqlite3_backup_step ()의 오류에 관계없이 여부에 관계없이 발생 
** sqlite3_backup_step ()가 완료되었습니다. 
** ^ 메모리 부족 상태 또는 IO 오류가 사전에 발생한 경우 
** sqlite3_backup_step ()와 같은 [sqlite3_backup 개체를 호출 
** sqlite3_backup_finish () 해당 오류 코드를 반환합니다. 
** 
[SQLITE_BUSY]의 ** ^ 반환 또는 SQLITE_LOCKED] sqlite3_backup_step에서 () 
** 영구 오류가 없다는 반환 값에는 영향을주지 않습니다 
** sqlite3_backup_finish (). 
** 
** [sqlite3_backup__remaining ()]] [[sqlite3_backup_pagecount ()]] 
** <B> sqlite3_backup_remaining ()와 sqlite3_backup_pagecount () </ B> 
** 
** ^ sqlite3_backup_step를 호출 할 때마다 ()의 내부 2의 값을 설정합니다 
** [sqlite3_backup 개체 : 페이지 수는 여전히 백업 
** 업 소스 데이터베이스 파일의 페이지 수의 합계. 
** sqlite3_backup_remaining ()와 sqlite3_backup_pagecount () 인터페이스 
**는 각각이 두 값을 가져옵니다. 
** 
** ^이 함수의 반환 값은 단지에 따라 업데이트됩니다 
** sqlite3_backup_step (). ^ 소스 데이터베이스 백업 중에 변경된 경우 
** 작업은 그 값은 정상을 고려하여 업데이트 될 수는 없습니다. 
** 업데이트해야하는 페이지 또는 원본 데이터베이스 파일 크기 
** 변경. 
** 
데이터베이스 핸들 ** <B> 동시 사용 </ B> 
** 
** ^ 소스 데이터베이스 연결은 다른 사람을 위해 응용 프로그램을 사용할 수 
** 목적 백업 작업이 진행 중이거나 초기화 된 상태. 
** ^ 만약 SQLite는 스레드로부터 안전 데이터베이스를 지원하도록 컴파일되어 구성되어있다 
** 연결은 소스 데이터베이스 연결을 동시에 사용할 수 
** 다른 스레드에서. 
** 
** 그러나 응용 프로그램이 안전해야 그 앞 
** 데이터베이스 연결을 한 후에 (모든 스레드에 의해) 다른 API에 전달되지 않습니다 
** sqlite3_backup_init ()를 호출하여 통화의 전에 
** sqlite3_backup_finish (). SQLite는 현재 여부는 확인되지 않습니다 
** 응용 프로그램이 잘못 대상에 액세스하는 경우 데이터베이스 연결 
** 때문에 오류 코드가보고되고 있지 않지만, 작업이 오동작 할 가능성 
** 그럼에도 불구하고. 먼저 데이터베이스 연결 사용하고 있습니다 만 
** 백업이 진행중인 것도 뮤텍스 교착 상태가 발생할 수 있습니다. 
** 
** 공유 캐시 모드에서 실행되는 경우 응용 프로그램이 필요 
** 보증 공유 캐시는 대상 데이터베이스에서 사용되는 것을 
백업 중 ** 사용되지 않는다. 사실, 이것은 수단 
** 응용 프로그램이 디스크 파일이 있는지 보장해야한다 
** 프로세스의 모든 연결에서 사용되지 않는 백업 
** sqlite3_backup_init에 전달 된 특정 연결뿐만 아니라, (). 
** 
** [sqlite3_backup 개체 자체는 부분적으로 스레드로부터 안전합니다. 여러 
** 스레드가 안전하게) (sqlite3_backup_step에 여러 개의 동시 호출을 할 수 있습니다. 
** 그러나 sqlite3_backup_remaining ()와 sqlite3_backup_pagecount () 
** API는 엄격하게 스레드 안전을 말하고 있지 않다. 그들이 호출 된 경우 
다른 스레드가 sqlite3_backup_step를 호출하는 것처럼 ** 동시에 ()가있는 
** 그들은 잘못된 값을 반환 할 수 있습니다. 
* /
SQLITE_API sqlite3_backup *sqlite3_backup_init(
  sqlite3 *pDest,                        /* Destination database handle */
  const char *zDestName,                 /* Destination database name */
  sqlite3 *pSource,                      /* Source database handle */
  const char *zSourceName                /* Source database name */
);
SQLITE_API int sqlite3_backup_step(sqlite3_backup *p, int nPage);
SQLITE_API int sqlite3_backup_finish(sqlite3_backup *p);
SQLITE_API int sqlite3_backup_remaining(sqlite3_backup *p);
SQLITE_API int sqlite3_backup_pagecount(sqlite3_backup *p);

/ * 
** CAPI3REF : 알림의 잠금을 해제 
** 
** ^ 공유 캐시 모드에서 실행하는 경우 데이터베이스 작업을 실패 할 수 있습니다 
** [SQLITE_LOCKED] 오류이면 공유 캐시 및 온 필요한 잠금 
** 공유 캐시의 개별 테이블을 얻을 수 없다. 보기 
** [SQLite의 공유 캐시 모드 공유 캐시 잠금에 대한 설명. 
** ^이 API는 SQLite를 호출하는 콜백을 등록하는 데 사용할 수있다 
** 연결이 현재 필요한 잠금을 유지하고있는 것은 그것을 포기합니다. 
라이브러리를 컴파일 한 경우 ** ^이 API는 제공되고 있습니다 
** [SQLITE_ENABLE_UNLOCK_NOTIFY C-전 처리기 기호가 정의되어있다. 
** 
** 참고 항목 : SQLite 잠금 해제 알림 기능을 사용. 
** 
데이터베이스 연결이 체결 때 ** ^ 공유 캐시 잠금이 해제된다 
** 그 현재의 트랜잭션 중 하나에 커밋하거나 롤백하여. 
** 
** ^ (차단 된 연결로 알려진) 연결을 얻을 수없는 
** 공유 캐시 잠금 SQLITE_LOCKED는 호출자에게 반환되는 
데이터베이스 연결 (블로킹 연결) ** 정체성 
** 필요한 리소스를 내부적으로 저장되는 잠겨 있습니다. ^ 후 
** 응용 프로그램이 SQLITE_LOCKED 오류를 받으면 호출 할 수 있습니다 
로 차단 된 연결 핸들에 ** sqlite3_unlock_notify () 메서드 
** 호출되는 콜백을 등록하기위한 첫 번째 인수 
** 블로킹 연결 현재 트랜잭션이 완결 될 때. ^ 
** 콜백은 [sqlite3_step 또는 sqlite3_close] 내에서 호출 
** 블로킹 연결 트랜잭션을 종료 콜. 
** 
** ^ (sqlite3_unlock_notify ()는 다중 스레드 응용 프로그램에서 호출 된 경우 
** 블로킹 연결이 이미 가지고 가능성이있다 
** sqlite3_unlock_notify ()가 호출 될 때까지 해당 트랜잭션을 종료했다. 
이러한 경우 ** 지정된 콜백이 즉시 시작되고 
** 호출 내에서 () sqlite3_unlock_notify한다. ) ^ 
** 
** ^ 차단​​ 된 연결에 기입 락을 취득하려고하는 경우 
** 공유 캐시 테이블 및 다른 몇몇 연결은 현재 보유하고있는 
** 같은 테이블에서 읽기 잠금은 다음 SQLite는 어떤 것을 선택 
** 다른 연결은 블로킹 연결로 사용합니다. 
** 
** ^ (이 등록 최대 하나의 잠금 해제 알림 콜백이 있을지도 모릅니다 
** 연결을 차단했다. sqlite3_unlock_notify는 () 때 불려 갔을 경우 
** 차단 된 연결이 이미 등록 된 잠금 해제를 알리는 콜백을 가지고 
** 새로운 콜백은 나이가 바뀝니다. ) ^ ^ sqlite3_unlock_notify ()가있는 경우 
** 둘째 인수로 NULL 포인터를 사용하여 호출되면 기존 
** 잠금 해제 알림 콜백은 취소됩니다. ^ 차단 된 연결 
** 잠금 해제를 알리는 콜백도 차단 닫을 취소되는 
** 사용하여 연결 [sqlite3_close을 (). 
** 
** 잠금 해제 알림 콜백은 재진입 없습니다. 응용 프로그램 호출 한 경우 
** 잠금 해제 알림 콜백 내에서 모든 sqlite3_xxx API 함수 
** 충돌 또는 교착 상태가 결과 일 가능성이있다. 
** 
** ^ 교착 상태가 발견되지 않으면 (아래 참조) sqlite3_unlock_notify ()은 항상 
** SQLITE_OK을 반환합니다. 
** 
** 콜백 호출에 대한 자세한 <B> </ B> 
** 
잠금 해제 알림 콜백이 등록 된 경우 **, 어플리케이션이 제공하는 
그것이 호출 할 때 콜백에 전달됩니다 ** 싱글은 void * 포인터. 
** 그러나 콜백 함수의 시그니처는 SQLite가 통과하는 것을 허용한다 
** 그것을 void * 컨텍스트 포인터의 배열입니다. 에 전달 된 첫 번째 인수 
** 잠금 해제 알림 콜백 void * 포인터의 배열에 대한 포인터이다 
** 두 번째 배열의 항목 수입니다. 
** 
블로킹 연결 트랜잭션이 체결되면 **이 있을지도 모른다 
** 잠금 해제 통지에 등록 된 여러 블록 연결 
** 콜백. ^ 2 이상이 같은 차단 된 연결이 지정된 경우 
** 같은 콜백 함수 대신 콜백 함수를 호출 
** 여러 번 그것은 void * 컨텍스트 포인터 세트로 한 번 시작됩니다 
** 배열로 묶어 차단 된 연결로 지정되었다. 
** 이것은 응용 프로그램의 모든 동작의 우선 순위를 결정하는 기회를 제공합니다 
** 차단되지 않은 데이터베이스 연결 설정 관련. 
** 
** <B> 교착 상태 감지 </ B> 
** 
** 후 잠금 해제를 알리는 콜백 A에 등록한다고 가정하면 
** 데이터베이스는 그 이상을 복용하기 전에 발행되는 콜백을 기다 
** 액션 (합리적인 가정), 그 다음이 API를 사용할 수 있습니다 
** 교착하는 응용 프로그램. 예를 들어, 포트 X를 기다리고있는 경우 
** 연결 와이즈 결론 트랜잭션 및 이와 유사한 연결 
** Y는 모두 연결하여 포트 X의 트랜잭션을 기다리는 
** 진행 시스템은 무한정 교착 된 상태이다. 
** 
**이 시나리오를 해결하기 위해 sqlite3_unlock_notify ()가 교착 상태를 실시해, 
** 감지. ^ sqlite3_unlock_notify에게 주어진 전화는 ()를 넣고 싶은 경우 
** 시스템 교착 상태는 SQLITE_LOCKED를 반환하고 
** 잠금 해제 알림 콜백이 등록되어있다. 시스템에 있다고 말하는 
** 교착 상태, 연결 A는 알림 잠금 해제를 위해 등록 된 경우 
** 연결 B의 트랜잭션이 종료되면 연결 콜백 
** B는 잠금 해제 알림 콜백에 자신을 등록 할 때 연결 
** A의 트랜잭션이 종료됩니다. ^ 간접적 인 교착 상태를 감지되므로, 
** 시스템은 또한 연결 B을 갖는 경우 교착하고 있다고 생각된다 
** 연결 체결 해제 ON-알림 콜백을 등록하고 
연결 C가 ^ 모든 연결 A 기다리고 있습니다. ** C 거래, 
** 간접 참조 수준의 수는 허용됩니다. 
** 
** "DROP TABLE"예외 <B> </ B> 
** 
[sqlite3_step ()에 대한 호출이 SQLITE_LOCKED을 돌려 줄 때 **, 그것은 거의 
** sqlite3_unlock_notify를 호출 할 필요 적절 (). 그러나 거기 
** 1 예외입니다. 의 "DROP TABLE"및 "DROP INDEX는"문장을 실행하는 경우 
** SQLite 검사 중 하나 현재 실행중인 SELECT 문이있는 경우 
** 동일한 연결에 속한다. 이 경우에는 SQLITE_LOCKED입니다 
** 돌아왔다. 이 경우 거기에는 "블로킹 연결"존재하지 않기 때문에 시작 
잠금 해제 알림 콜백임을 ** sqlite3_unlock_notify ()의 결과 
** 즉시 호출되었다. 그런 다음 응용 프로그램은 "DROP TABLE을"다시 시도하는 경우 
** 또는 "DROP INDEX"쿼리 무한 루프가 결과 일 가능성이 있습니다. 
** 
**이 문제를 해결하는 한 가지 방법은 반환 된 확장 오류 코드를 확인하는 것입니다 
** sqlite3_step () 호출. ^ (블로킹 연결이 존재하는 경우, 
** 확장 오류 코드가 SQLITE_LOCKED_SHAREDCACHE로 설정되어 있습니다. 그렇지 않으면, 안 
** 특별한 "의 DROP TABLE / INDEX"의 경우 확장 오류 코드는 단지이다 
** SQLITE_LOCKED. ) ^ 
* /
SQLITE_API int sqlite3_unlock_notify(
  sqlite3 *pBlocked,                          /* Waiting connection */
  void (*xNotify)(void **apArg, int nArg),    /* Callback function to invoke */
  void *pNotifyArg                            /* Argument to pass to xNotify */
);

/ * 
** CAPI3REF : 문자열 비교 
** 
** ^ [sqlite3_stricmp () 및 sqlite3_strnicmp () API는 응용 프로그램에 허용 
UTF-8을 포함한 2 버퍼의 내용을 비교한다. **로 확장 
케이스에 의존하지 않는 형식으로 ** 문자열 "케이스의 동일한 정의를 사용하여 
** 식별자를 비교할 때 SQLite가 내부적으로 사용합니다 독립 " 
* /
SQLITE_API int sqlite3_stricmp(const char *, const char *);
SQLITE_API int sqlite3_strnicmp(const char *, const char *, int);

/ * 
** CAPI3REF : 문자열 glob 동작 
* 
** ^ [sqlite3_strglob (P, X) 인터페이스 수익이 제로의 경우, 문자열 X의 경기 
X 문자열이 일치하지 않는 경우 ** 그로스 패턴 P는 그것이 아닌 0을 반환 
** 그로스 패턴은 P. ^ 그로스 패턴 매칭의 정의에 사용되는 
** [sqlite3_strglob (P, X) "X 그로스 P"연산자의 경우와 동일합니다 
** SQLite는에서 사용되는 SQL 언어. ^ sqlite3_strglob는 (P, x) 함수는 대문자이다 
** 민감합니다. 
** 
**이 루틴이 일치하고 0이 아닌 제로에주의하십시오 경우 문자열 
** [sqlite3_stricmp () 및 sqlite3_strnicmp ()와 같은과 일치하지 않습니다. 
* /
SQLITE_API int sqlite3_strglob(const char *zGlob, const char *zStr);
/ * 
** CAPI3REF : 오류 로깅 인터페이스 
** 
** ^ [sqlite3_log는 () 인터페이스, 오류 로그에 메시지를 기록 
** [sqlite3_config ()]에서 [SQLITE_CONFIG_LOG 옵션으로 설치했습니다. 
로그가 활성화되어있는 경우 ** ^ zFormat 문자열과 그 뒤에 이어지는 인수는 
** 최종 출력 문자열을 생성하는 [sqlite3_snprintf ()와 함께 사용. 
** 
** sqlite3_log () 인터페이스는 다음과 같은 확장 기능으로 사용하기위한 것입니다 
** 가상 테이블, 데이터 함수, SQL 함수. 있지만 
**) sqlite3_log을 (호출에서 응용 프로그램을 방지하기 위해, 아무것도, 이렇게 할 수 없습니다 
**는 나쁜 형태로 간주됩니다. 
** 
** zFormat 문자열이 NULL 일 수 없습니다. 
** 
** 교착 상태 및 기타 스레딩 문제를 해결하려면 sqlite3_log () 루틴 
** 동적으로 할당 된 메모리를 사용하는 것은 아닙니다. 로그 메시지가 내부에 저장되어있는 
** 스택의 고정 길이 버퍼. 로그 메시지는 더 긴 경우 
백 ** 일부 문자는 길이로 잘립니다 
** 버퍼. 
* /
SQLITE_API void sqlite3_log(int iErrCode, const char *zFormat, ...);

/ * 
** CAPI3REF : 로그 선행 기입 후크를 커밋 
** 
** ^ [sqlite3_wal_hook () 함수가 콜백을 등록하는 데 사용되는 
** 데이터베이스 연결이 데이터를 커밋 할 때마다 호출됩니다 
** [로그 선행 기입 (즉, 트랜잭션이 커밋 될 때마다 
** [journal_mode | journal_mode = WAL 모드). 
** 
** ^ 콜백은 커밋이 이루어진 후에 SQLite에 의해 시작되고 
출시 된 데이터베이스이므로 구현에 ** 관련 쓰기 잠금 
필요한 경우 ** 데이터베이스를 읽기, 쓰기 또는 체크 포인트]가 있습니다. 
** 
** ^ 그것이 호출 할 때 콜백 함수에 전달 된 첫 번째 매개 변수 
**시) (sqlite3_wal_hook에 전달 세번째 매개 변수의 복사본입니다 
** 콜백을 등록한다. ^ 둘째는 데이터베이스 핸들의 복사본입니다. 
** ^ 3 번째의 파라미터는에 기록 된 데이터베이스의 이름입니다 - 
** '기본'또는 첨부]-ED 데이터베이스의 이름 중 하나. ^ 네번째 매개 변수 
현재 ** 미리 쓰기 로그 파일의 페이지 수이며, 
** 만 커밋 된 것도 포함한다. 
** 
** 콜백 함수는 일반적으로 [SQLITE_OK] 반환해야합니다. ^ 않으면 오류 
** 코드를 반환하고 오류를 통해서 다시 전파 
콜백을 일으킨 문장을 일으킬 ** SQLite의 코드 기반 
커밋은 아직 발생하는 것이지만 ** 오류를보고한다. 만약 
** 콜백이 반환 [SQLITE_ROW 또는 SQLITE_DONE 또는 그 값을 반환하는 경우 
** 그 결과 유효한 SQLite 오류 코드에 대응하지 않는 
** 정의되어 있지 않습니다. 
** 
** 단일 데이터베이스 핸들은 대부분의 싱글 미리 쓰기 로그의 콜백 가지고 가능성 
** 1 번에 등록되어 있습니다. ^ 호출 [sqlite3_wal_hook을 ()] 중 하나를 대체 
** 이전에 미리 쓰기 로그 콜백을 등록했습니다. ^ 있다는 점에 유의하십시오 
** [sqlite3_wal_autocheckpoint () 인터페이스와 
** [wal_autocheckpoint 프라 그마] 두 호출 [sqlite3_wal_hook ()]가됩니다 
** 그들은 사전에서 sqlite3_wal_hook () 설정을 덮어 씁니다. 
* /
SQLITE_API void *sqlite3_wal_hook(
  sqlite3*, 
  int(*)(void *,sqlite3*,const char*,int),
  void*
);

/ * 
** CAPI3REF : 자동 검사 점을 설정합니다 
** 
** ^ [sqlite3_wal_autocheckpoint (D, N)]에 대한 래퍼입니다 
** 데이터베이스 연결에 모든 데이터베이스를 일으키는 원인 [sqlite3_wal_hook ()] D 
** 자동으로 체크 포인트] 
** 트랜잭션을 커밋 한 후이 있고, N 인 경우, 또는 
로그 선행 기입] 파일의 ** 더 프레임. ^ 제로를 전달하거나 
** nFrame를 매개 변수로 음수 값은 자동 비활성화합니다 
** 체크 포인트를 완전히. 
** 
** ^이 함수로 등록 된 콜백은 기존의 콜백을 대체 
** 사용하여 등록 [sqlite3_wal_hook을 (). ^ 마찬가지로 콜백을 등록하는 
** 사용하여 sqlite3_wal_hook 것은 () 자동 검사 점 메커니즘을 비활성화합니다 
**이 함수로 구성되었다. 
** 
** ^ [wal_autocheckpoint 프라 그마]이 인터페이스를 호출하는 데 사용할 수 있습니다 
** SQL에서. 
** 
** ^ 모든 새 데이터베이스 연결 자동 검사 점을 가지는 디폴트 
** 1000 년 임계 값 또는 SQLITE_DEFAULT_WAL_AUTOCHECKPOINT에서 활성화 
** 페이지. 이 인터페이스의 사용 
기본 설정은 최적 이하인 것으로 나타났다 경우에만 필요하다. ** 
** 특정 용도를 위해. 
* /
SQLITE_API int sqlite3_wal_autocheckpoint(sqlite3 *db, int N);

/ * 
** CAPI3REF : 체크 포인트 데이터베이스 
** 
** ^ [sqlite3_wal_checkpoint (D, X) 인터페이스는 데이터베이스의 이름 X를 일으킬 
** 데이터베이스 연결 D의 체크 포인트 및. ^ 만약 X가 NULL 또는있는 
** 빈 문자열, 체크 포인트가 모든 데이터베이스에서 실행되는 
** 연결 D. ^ 데이터베이스 연결 D가 비슷 않는 경우 
** [WAL는 | 미리 쓰기 로깅 모드이 인터페이스는 무해 무 조작입니다. 
** 
** ^ [wal_checkpoint 프라 그마]이 인터페이스를 호출하는 데 사용할 수 있습니다 
** SQL에서. ^ [sqlite3_wal_autocheckpoint () 인터페이스와 
** [wal_autocheckpoint 프라 그마]이 인터페이스가있는 것이 원인이라고하는 데 사용할 수있는 
WAL 특정 크기 임계 값에 도달 할 때마다 **를 실행합니다. 
** 
** 참조 : [sqlite3_wal_checkpoint_v2을 () 
* / 
SQLITE_API int sqlite3_wal_checkpoint(sqlite3 *db, const char *zDb);

/ * 
** CAPI3REF : 체크 포인트 데이터베이스 
** 
** WAL 데이터베이스 ZDB 검사 점 작업을 수행하여 데이터베이스에 연결되어 
** 핸들 dB. 구체적인 동작의 값에 의해 결정된다 
** EMODE 매개 변수 : 
** 
** <DL> 
** <DT> SQLITE_CHECKPOINT_PASSIVE <DD> 
많은 프레임 등 ** 체크 포인트의 모든 데이터베이스를 기다리지 않고 
** 리더 나 라이터는 종료합니다. db 파일을 동기화하려면 로그의 모든 프레임 
** 체크 포인트되어 있습니다. 이 모드에서는 호출과 같습니다. 
** sqlite3_wal_checkpoint (). 바쁜 처리기 콜백이 불려 갈 것은 없습니다. 
** 
** <DT> SQLITE_CHECKPOINT_FULL <DD> 
나시가있을 때까지 **이 모드 블록 (바쁜 처리기 콜백이 호출됩니다) 
** 데이터베이스 작성자 및 모든 독자는 최신 데이터베이스에서 읽고있다 
** 스냅 샷. 그런 다음 로그 파일에 모든 프레임을 체크 포인트와 동기화 
** 데이터베이스 파일. 이 호출을 차단하고, 데이터베이스의 작성자는, 실행 중, 
** 대신 데이터베이스의 독자. 
** 
** <DT> SQLITE_CHECKPOINT_RESTART <DD> 
**이 모드는 다음을 제외하고 SQLITE_CHECKPOINT_FULL처럼 작동합니다 
** 로그 파일 그것을 차단의 체크 포인트는 (바쁜 핸들러 콜백이 호출됩니다) 
** 모든 독자가 유일한 데이터베이스 파일에서 읽고있을 때까지. 이것은 확실하게 
** 데이터베이스 파일에 쓸 수있는 다음 클라이언트는 로그 파일을 다시 시작 
** 처음부터. 이 호출을 차단하고, 데이터베이스의 작성자는, 실행 중, 
** 대신 데이터베이스의 독자. 
** </ DL> 
** 
pnLog가 NULL이 아닌 경우 **는 * pnLog 내의 프레임 수로 설정되어있는 
** 가기 전에 로그 파일. pnCkpt가 NULL이 아닌 경우 * pnCkpt는 다음과 같이 설정 
(이미 있었다는 것을 어느 쪽이든을 포함 체크 포인트의 프레임 ** 총 
**이 함수가 호출 될 때) 검문소. * pnLog과 * pnCkpt 할 수있다 
** sqlite3_wal_checkpoint_v2 ()이 SQLITE_OK 이외를 반환해도 이식됩니다. 
이 항목은 오류로 인해 사용할 수없는 경우 **, 그들은 모두 설정되어있다 -1 
** 호출자에게이를 통신하기 위해 돌아온다. 
** 
** 모든 호출은 데이터베이스 파일을 단독 "체크 포인트"잠금을 획득. 만약 
** 다른 프로세스가 동시에 체크 포인트 작업을 수행하고있다 
** 잠금을 얻지 못하고, SQLITE_BUSY가 반환됩니다. 이 있어도 
** 바쁜 핸들러가 설정되고 그것은이 경우에는 호출되지 않습니다. 
** 
** SQLITE_CHECKPOINT_FULL 및 다시 시작 모드도 배제를 가져 
데이터베이스 파일에 ** "작가"잠금. 쓰기 잠금을 얻을 수없는 경우 
** 빨리, 그리고 바쁜 처리기는 설정되어 있는지를 호출하여 작가 
바쁜 처리기 중 하나가 0을 반환하거나 고정 될 때까지 ** 잠금을 다시 시도 함 
** 취득에 성공. 기다리는 동안 바쁜 처리기 호출 될 
** 데이터베이스 독자 전술 한대로. 바쁜 처리기는 전에 0이 반환 된 경우 
** 작성기 잠금을 가져오고 데이터베이스의 독자를 기다리는 동안에되고 
뿐만 아니라 그 시점에서 ** 검문소 진행 
** SQLITE_CHECKPOINT_PASSIVE - 가능한 한 체크 포인트로 많은 프레임 
** 더 이상 차단하지 않고. SQLITE_BUSY이 경우에 반환됩니다. 
** 
** 매개 변수 ZDB가 NULL 또는 길이 제로의 캐릭터 라인을 가리키는 경우 
** 지정된 작업은 모든 WAL 데이터베이스에서 시도되고 있습니다. 이 경우 
** 출력 매개 변수에 기록 된 값이 pnLog을 *와 * pnCkpt은 정의되어 있지 않습니다. 만약 
하나 이상을 처리 할 때 ** SQLITE_BUSY 오류가 발생한 
** WAL 데이터베이스 연결 작업이 아직 남아있는쪽으로 시도 된 
** 데이터베이스를 연결하고 SQLITE_BUSY가 호출자에게 반환됩니다. 있다고하더라도, 다른 
연결된 데이터베이스 처리 중에 ** 오류가 발생하여 작업이 중단됩니다 
** 오류 코드는 즉시 호출자에게 돌려 보냈다. 오류가없는 경우 
첨부 처리 중 ** (SQLITE_BUSY 또는 기타)가 발생했습니다 
** 데이터베이스는 SQLITE_OK가 반환됩니다. 
** 
** 데이터베이스 ZDB는 WAL에 포함되지 않은 연결된 데이터베이스의 이름 인 경우 
** 모드 SQLITE_OK를 반환하고 두 * pnLog과 * pnCkpt는 -1로 설정되어 있습니다. 만약
** ZDB는 NULL (또는 길이 제로의 캐릭터 라인)이 아닌 하나의 이름이 없습니다. 
** 데이터베이스를 연결, SQLITE_ERROR는 호출자에게 반환됩니다. 
* /
SQLITE_API int sqlite3_wal_checkpoint_v2(
  sqlite3 *db,                    /* Database handle */
  const char *zDb,                /* Name of attached database (or NULL) */
  int eMode,                      /* SQLITE_CHECKPOINT_* value */
  int *pnLog,                     /* OUT: Size of WAL log in frames */
  int *pnCkpt                     /* OUT: Total number of frames checkpointed */
);

/ * 
** CAPI3REF : 검사 점 작업 매개 변수 
** 
**이 상수는 세 번째 매개 변수로 사용할 수있다 
** [sqlite3_wal_checkpoint_v2 (). 참조 [sqlite3_wal_checkpoint_v2을 () 
**의 의미와 사용에 대한 자세한 내용은 문서 
**이 값의 각각. 
* /
#define SQLITE_CHECKPOINT_PASSIVE 0
#define SQLITE_CHECKPOINT_FULL    1
#define SQLITE_CHECKPOINT_RESTART 2

/ * 
** CAPI3REF : 가상 테이블 인터페이스 설정 
** 
**이 함수는, 어느 쪽이든 [특정 연결 또는 xCreate] 메서드에서 호출 할 수 있습니다 
** 가상 테이블의 구현을 설정하려면 
가상 테이블 인터페이스 ** 다양한 측면. 
** 
**이 인터페이스는 특정 연결 또는 컨텍스트 외부에서 호출 된 경우 
** xCreate 가상 테이블 메서드는 동작은 보증되지 않습니다. 
** 
** 현재 사용하고 구성되어 있어도 좋은 유일한 가지 옵션이 있습니다 
**이 기능. (SQLITE_VTAB_CONSTRAINT_SUPPORT를 참조하십시오.) 기타 옵션을 
** 향후에 추가 될 수있다. 
* / 
SQLITE_API int sqlite3_vtab_config(sqlite3*, int op, ...);

/ * 
** CAPI3REF : 가상 테이블 설정 옵션 
** 
**이 매크로는 다양한 옵션을 정의 할 
** [sqlite3_vtab_config () 인터페이스 가상 테이블 구현 
** 그들의 동작을 사용자 정의하고 최적화하는 데 사용할 수있다. 
** 
** <DL> 
** <DT> SQLITE_VTAB_CONSTRAINT_SUPPORT 
양식 ** <DD> 통화 
** [sqlite3_vtab_config (DB, SQLITE_VTAB_CONSTRAINT_SUPPORT, X)가 지원되어 있습니다 만, 
** X는 정수이다. X가 제로의 경우 가상 테이블이 
** [xCreate 또는 특정 연결] 메서드가 호출 [sqlite3_vtab_config ()하지 않습니다 
** 지원 제한. 이 구성이면 (이것이 디폴트입니다) 
** [의 XUpdate] 메서드의 호출은, 모든 다음에, SQLITE_CONSTRAINT] 반환 값 
[| 중지 분쟁에 관한]이되어 있던 것처럼 ** 문장은 롤백됩니다 
** 사용자의 SQL 문의 일부로 지정되어 관계없이 실제 
** 지정된 충돌 모드 ON. 
** 
X ** 0이 아닌 경우 가상 테이블의 구현을 보증 
리턴즈 [SQLITE_CONSTRAINT] [의 XUpdate] 있으면 **, 그것은 전에 이렇게하는 것을
** 내부 또는 영구적 인 데이터 구조에 변화가 이루어지고있다. 
** [CONFLICT ON 모드에서는 ABORT, FAIL 무시하거나 ROLLBACK, SQLite한다면 
** 문 또는 데이터베이스의 트랜잭션을 롤백 할 수 포기 
** 또는 필요에 따라 현재 SQL 문장의 처리를 계속. 
** 온 경쟁 모드를 교환하여 된 경우의 XUpdate] 메서드가 반환 
** [SQLITE_CONSTRAINT, SQLite는 온 경쟁 모드 것처럼 이것을 처리 
** 중단되어 있었다. 
** 
핸들 또는 대체하기 위하여 필요로된다. ** 가상 테이블 구현 
** [의 XUpdate] 메서드에서 수행해야합니다. 호출 경우 
** [sqlite3_vtab_on_conflict () 기능을 설명하며, 이러한 온 전류 
** 충돌 정책은 REPLACE 가상 테이블 구현해야한다 
** 침묵의 XUpdate 콜백의 해당 행을 교환하고 
** SQLITE_OK을 반환합니다. 이것이 불가능한 경우, 그것은 반환 할 수 있습니다 
SQLite는 다시 중단 폴이 경우 ** SQLITE_CONSTRAINT, 
** 제약이 취급한다. 
** </ DL> 
* /
#define SQLITE_VTAB_CONSTRAINT_SUPPORT 1

/ * 
** CAPI3REF : 가상 테이블의 경쟁 정책을 결정 
** 
**이 함수는의 XUpdate] 메서드 호출 내에서 호출 할 수 있습니다 
** 가상 테이블의 INSERT 또는 UPDATE 작업의 구현. ^ 
** 반환되는 값은 SQLITE_FAIL, SQLITE_IGNORE, SQLITE_ROLLBACK]의 하나이며, 
** [SQLITE_ABORT] 또는 SQLITE_REPLACE, ON CONFLICT 모드에 따라 
**에서의 XUpdate] 메서드 호출을 트리거 한 SQL 문 
** 가상 테이블. 
* /
SQLITE_API int sqlite3_vtab_on_conflict(sqlite3 *);

/ * 
** CAPI3REF : 충돌 해결 모드 
** 
**이 상수에 [sqlite3_vtab_on_conflict ()에서 반환되는 
** 가상 테이블 구현 무엇을 [ON CONFLICT 모드를 알리는 
** 평가되는 SQL 문입니다. 
** 
** [SQLITE_IGNORE] 상수도 전위로 사용되는 것에주의하십시오 
**의 반환 값 [sqlite3_set_authorizer () 콜백하면 
** [SQLITE_ABORT]도 결과 코드입니다. 
* /
#define SQLITE_ROLLBACK 1
/* #define SQLITE_IGNORE 2 // Also used by sqlite3_authorizer() callback */
#define SQLITE_FAIL     3
/* #define SQLITE_ABORT 4  // Also an error code */
#define SQLITE_REPLACE  5



/*
** Undo the hack that converts floating point types to integer for
** builds on processors without floating point support.
*/
#ifdef SQLITE_OMIT_FLOATING_POINT
# undef double
#endif

#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif /* _SQLITE3_H_ */

/*
** 2010 August 30
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
*/

#ifndef _SQLITE3RTREE_H_
#define _SQLITE3RTREE_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct sqlite3_rtree_geometry sqlite3_rtree_geometry;

/*
** Register a geometry callback named zGeom that can be used as part of an
** R-Tree geometry query as follows:
**
**   SELECT ... FROM <rtree> WHERE <rtree col> MATCH $zGeom(... params ...)
*/
SQLITE_API int sqlite3_rtree_geometry_callback(
  sqlite3 *db,
  const char *zGeom,
#ifdef SQLITE_RTREE_INT_ONLY
  int (*xGeom)(sqlite3_rtree_geometry*, int n, sqlite3_int64 *a, int *pRes),
#else
  int (*xGeom)(sqlite3_rtree_geometry*, int n, double *a, int *pRes),
#endif
  void *pContext
);


/*
** A pointer to a structure of the following type is passed as the first
** argument to callbacks registered using rtree_geometry_callback().
*/
struct sqlite3_rtree_geometry {
  void *pContext;                 /* Copy of pContext passed to s_r_g_c() */
  int nParam;                     /* Size of array aParam[] */
  double *aParam;                 /* Parameters passed to SQL geom function */
  void *pUser;                    /* Callback implementation user data */
  void (*xDelUser)(void *);       /* Called by SQLite to clean up pUser */
};


#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

#endif  /* ifndef _SQLITE3RTREE_H_ */

