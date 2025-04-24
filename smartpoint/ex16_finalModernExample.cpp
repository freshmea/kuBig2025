// 목표 : STL 과 스마트포인터를 사용해서 데이터베이스 엔진 만드세요.
// 스마트 포인터 활용 shared_ptr, unique_ptr
// 쓰레드 활용 multithread, mutex, atomic -> 내부 동기화 위한 락 구조 설계
// 데이터 삽입 insert(key(int), value(string));
// 데이터 검색 find(key);
// 데이터 삭제 remove(key);
// class DataBase
// 저장용 컨테이너 - unordered_map 참조에 특화된!!
// 컬럼 추가(타입 정하기) - .. 도전 하실분만!
