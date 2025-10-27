cc_binary( # 바이너리 실행규칙
    name = "main",  # 타겟 이름 (Label: //main:main)
    srcs = ["main.cpp"], # 입력 소스 파일
    deps = [
        "//lib:hello_app",
        "@libusb//:libusb"
    ],
    copts = ["-std=c++20"]
)


