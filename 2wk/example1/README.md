# 3+4 C ↔ Assembly 비교 (MSYS2 + VS Code)

## 사전 준비
- MSYS2 설치 후 UCRT64 환경에서 다음 패키지 설치:
  ```bash
  pacman -Syu
  pacman -S --needed mingw-w64-ucrt-x86_64-toolchain flex bison gdb make
  ```

## VS Code에서 열기
1. 이 폴더를 VS Code로 엽니다.
2. 터미널을 열면 자동으로 **MSYS2 UCRT64**가 실행되게 설정되어 있습니다(`.vscode/settings.json`).

## 빌드/실행/ASM 생성
- 빌드: **Ctrl+Shift+B** → `Build (make)`
- 실행: `Terminal → Run Task… → Run` 또는 `make run`
- C → ASM 소스 생성: `Terminal → Run Task… → ASM (make asm)` → `main.S` 생성
- 실행 파일 디스어셈블: `Terminal → Run Task… → Disasm (make disasm)` → `main.disasm.txt` 생성

## 파일 설명
- `main.c` : 3+4를 더해 출력
- `main.S` : 위 C를 컴파일러가 생성한 **어셈블리(소스)** (Intel 문법)
- `three_plus_four.exe` : 빌드 결과 실행 파일
- `main.disasm.txt` : 실행 파일의 **디스어셈블** 결과 (Intel 문법)

## 디버깅
- `F5` → `Debug three_plus_four (gdb)` 선택
- 브레이크포인트를 `add()`나 `main()`에 걸어 레지스터/스택을 확인하세요.

즐코딩!
