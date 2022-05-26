# docker-runtime-c

## 1. 개요
본 저장소는 C언어로 작업된 코드를 빌드하고, 도커 컨테이너 환경에서 실행하기 위한 작업 공간입니다.

## 2. 저장소 구성
본 저장소의 구성은 다음과 같습니다.
- README.md: 작업 공간 안내 파일 (현재 파일)
- src: C언어로 작업된 코드가 있는 경로
  - 현재 src에는 **main.c 파일 하나만 존재**하며, 아래 명령 및 환경 또한 **main.c 파일만을 위해 작업**되어있음
  - main.c는 두 개의 pthread가 각각 2초, 5초 단위로 현재 시간을 출력하는 내용이 담긴 소스코드
- docker: 도커 컨테이너를 위한 경로이며, src에 있는 C언어 코드 빌드와 도커 컨테이너 이미지 생성을 위한 Dockerfile이 있음
- Makefile: 도커 컨테이너 빌드 및 생성, 실행, 종료 등 명령들이 있는 프로그램 설정 파일

## 3. 사용 방법
Makefile에 정리된 아래의 명령 집합을 통해 도커 컨테이너를 생성, 실행, 중단 할 수 있음

### 3-1. C코드 및 도커 컨테이너 빌드
```
$ make build-docker
```
위 명령은 src 폴더에 있는 C코드들을 빌드하고, 생성된 바이너리를 포함하여 도커 컨테이너 이미지를 빌드(생성) 합니다. </br>
C코드 빌드를 위한 명령은 docker/Dockerfile 내 기재 되어 있으며, 코드 추가 및 변경 시 빌드 환경에 맞추어 해당 내용의 수정이 필요합니다.

### 3-2. 도커 이미지 실행
```
$ make run-docker
```
3-1 과정을 통해 빌드된 도커 컨테이너 이미지를 실행합니다. </br>
도커 이미지는 커널 등 시스템 자원 접근이 가능한 **privileged 모드로 수행**하며, 자세한 내용은 아래 url을 참고하세요. </br>
https://docs.docker.com/engine/reference/run/#runtime-privilege-and-linux-capabilities

### 3-3. 실행 중인 도커 이미지 접근
```
$ make exec-docker
```
3-2 과정을 통해 실행중인 도커 이미지를 대상으로 sh(/bin/sh) 접근을 위한 명령입니다. </br>
이는 3-2를 통해 반드시 도커 이미지가 실행 중이어야 합니다.

### 3-4. 도커 이미지 실행 종료
```
$ make rm-docker
```
실행 중인 도커 이미지를 종료합니다.

## 4. 실행 중인 도커 이미지의 출력문 확인
C 코드에서 printf와 같이 출력 구문을 사용하여 도커 이미지를 실행했다면, 아래의 과정을 통해 내용을 확인할 수 있습니다.

### 4-1. 컨테이너 ID 확인
```
$ docker ps -a

CONTAINER ID   IMAGE             COMMAND               CREATED         STATUS         PORTS     NAMES
64f74d376e55   jgkimapp:v0.1.0   "/bin/sh -c ./main"   3 seconds ago   Up 2 seconds             jgkimapp
```
위 명령을 통해, CONTAINER ID를 확인합니다.

### 4-2. 실행 중인 이미지의 출력문 확인
```
$ docker logs <CONTAINER ID>
```
```
$ docker logs 64f74d376e55

timerB: 2022-5-26 11:25:20
timerA: 2022-5-26 11:25:20
timerA: 2022-5-26 11:25:22
timerA: 2022-5-26 11:25:24
timerB: 2022-5-26 11:25:25
timerA: 2022-5-26 11:25:26
timerA: 2022-5-26 11:25:28
timerB: 2022-5-26 11:25:30
timerA: 2022-5-26 11:25:30
timerA: 2022-5-26 11:25:32
timerA: 2022-5-26 11:25:34
timerB: 2022-5-26 11:25:35
...
```
