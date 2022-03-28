# beacon-flood

802.11에서 AP는 자신의 존재를 알리기 위해 주기적으로 beacon frame을 브로드 캐스트 하고, Station에서 해당 frame을 수신하게 되면 주변에 어떤 무선 공유기들이 있는지 알 수 있습니다. 이로부터 임의의 패킷을 생성해서 마치 실제 AP가 존재하는 것 처럼 Station에서 착각하게끔 하는 beacon frame을 만들어볼 수 있습니다. 작성한 프로그램은 무선랜 인터페이스와, 인자로 원하는 ssid 목록이 담긴 파일을 주어 실행하게 되면 fake beacon frame을 만들어서 브로드캐스트하는 기능을 합니다.

실험 결과 fake beacon frame의 AP mac 주소가 항상 동일할 경우 Station에서 인식하지 않는 문제가 있어서, 주기적으로 randomize_bssid()라는 함수를 호출해서 AP의 mac 주소를 바꿔주었습니다.
