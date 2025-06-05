---

学籍番号: 202301330
名前: 長田 悠生
課題番号：2
練習問題番号：211, 105
題名：文字列操作

[環境]
OSの環境等は以下の通りである。

OS: NixOS 25.05 (Warbler) x86_64
gcc version: 14.2.1 20241116

以下のshell.nixの環境で課題に取り組んだ。

```nix
{
  pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-25.05") { },
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
  ];
}
```

[練習問題211 概要]
標準入力から読み込んだデータ中の空白をピリオドに、アルファベットの
小文字を大文字に変換するプログラムを作成した。
また、TSUKUBAという文字列を検知したら、I found TSUKUBA!という
標準エラー出力を出力するようにした。

[練習問題211 実行結果]

全ての空白がピリオドに変換され、
全ての小文字が大文字に変換されていることが
結果から明らかである。
また、TSUKUBAの文字が文字列内のどこに存在していても、
標準エラー出力のメッセージ I found TSUKUBA! が
出力されていることがわかる。

```sh
$ gcc -g task211.c
$ ./a.out
Hello World!
HELLO.WORLD!
TSUKUBA
I found TSUKUBA!

tsukuba
TSUKUBA
TSUKUB
TSUKUB
TSUKUBAhello
I found TSUKUBA!
HELLO
helloTSUKUBA
I found TSUKUBA!
HELLO
helloTSUKUBAworld
I found TSUKUBA!
HELLOWORLD
```

[練習問題211 考察]
出力結果から、練習問題211の題意を満たすことができた。
TSUKUBAの文字列検出を泥臭い方法で行っているが、
一行ずつ標準入力を受け取ることでもう少しスマートに
書けたかもしれないと考えている。

[練習問題211 プログラム]

- コマンドライン引数について

コマンドライン引数を受け取ったときに、標準エラー出力を
出力するために、あえてmain関数はコマンドライン引数を
受け付けるようにしている。

- TSUKUBAという文字列の検知について

Tに該当するASCIIの文字コードが検出された際には、
続く文字列がSUKUBAであるかどうかを判定する。
続く文字列がSUKUBAでない場合に備えて、
TSUKUBAの文字列の検出モードに入ったら、
その文字列のバッファをtsukuba_bufに保存している。
続く文字列がSUKUBAでなかった場合は、
tsukuba_bufに保存したASCIIコードを
一文字ずつ標準出力している。

- 空白と小文字の変換について

空白と小文字の変換は、char_conveter関数によって、
一文字ずつ変換している。

```c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define TSUKUBA_LEN 7

void char_converter(char c) {
    if (isblank(c)) {
        // convert blank to period
        putchar('.');
    } else if (islower(c)) {
        // convert lower case to upper case
        putchar(toupper(c));
    } else {
        // other characters remain unchanged
        putchar(c);
    }
}

int main(int argc, char const *argv[]) {
    int c;
    // TSUKUBA counter
    int tsukuba_cnt = 0;
    // TSUKUBA buffer
    char tsukuba_buf[TSUKUBA_LEN];

    // if command line arguments are given, print usage message
    if (argc > 1) {
        fprintf(stderr, "This program cannot take command line arguments.\n");
        exit(1);
    }

    while ((c = getchar()) != EOF) {
        // check for "TSUKUBA" in the input
        if (c == 84) {  // ASCII code for 'T'
            tsukuba_cnt++;
            tsukuba_buf[0] = c;  // store 'T' in buffer
            tsukuba_buf[1] = '\0';
        } else if (c == 83 && tsukuba_cnt == 1) {  // ASCII code for 'S'
            tsukuba_cnt++;
            tsukuba_buf[1] = c;  // store 'S' in buffer
            tsukuba_buf[2] = '\0';
        } else if (c == 85 && tsukuba_cnt == 2) {  // ASCII code for 'U'
            tsukuba_cnt++;
            tsukuba_buf[2] = c;  // store 'U' in buffer
            tsukuba_buf[3] = '\0';
        } else if (c == 75 && tsukuba_cnt == 3) {  // ASCII code for 'K'
            tsukuba_cnt++;
            tsukuba_buf[3] = c;  // store 'K' in buffer
            tsukuba_buf[4] = '\0';
        } else if (c == 85 && tsukuba_cnt == 4) {  // ASCII code for 'U'
            tsukuba_cnt++;
            tsukuba_buf[4] = c;  // store 'U' in buffer
            tsukuba_buf[5] = '\0';
        } else if (c == 66 && tsukuba_cnt == 5) {  // ASCII code for 'B'
            tsukuba_cnt++;
            tsukuba_buf[5] = c;  // store 'B' in buffer
            tsukuba_buf[6] = '\0';
        } else if (c == 65 && tsukuba_cnt == 6) {  // ASCII code for 'A'
            // reset tsukuba_cnt
            tsukuba_cnt = 0;
            // initialize buffer
            tsukuba_buf[0] = '\0';
            fprintf(stderr, "I found TSUKUBA!\n");
        } else if (tsukuba_cnt > 0) {
            // if not complete "TSUKUBA", show buffer string
            if (tsukuba_cnt < 7) printf("%s", tsukuba_buf);

            // reset tsukuba_cnt if not matching
            tsukuba_cnt = 0;

            // other characters
            char_converter(c);
        } else {
            // other characters
            char_converter(c);
        }
    }

    return 0;
}
```

[練習問題105 概要]

[練習問題105 実行結果]

```sh
$ gcc -g task105.c
$ ./a.out
strlcpy time: 0.654431
average of strlcpy time: 0.000654
my_strlcpy time: 3.372593
average of my_strlcpy time: 0.003373
strdup time: 0.643938
average of strdup time: 0.000644
my_strdup time: 3.451284
average of my_strdup time: 0.003451
```

[練習問題105 考察]

[練習問題105 プログラム]

- my_strlcpy関数

```c
#include <string.h>

size_t my_strlcpy(char *dst, const char *src, size_t size) {
    // get src length
    size_t src_len = strlen(src);
    // copy up to size - 1 characters from src to dst
    size_t actual_size = size - 1;
    for (size_t i = 0; i < actual_size; i++) {
        dst[i] = src[i];
    }
    // set null the end of the destination string
    dst[actual_size] = '\0';

    return src_len;
}

```

- my_strdup関数

```c
#include <string.h>

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    //  validate about creating malloc
    if (new_str == NULL) {
        return NULL;
    }
    // copy
    for (size_t i = 0; i <= len; i++) {
        new_str[i] = s[i];
        // set null the end of the new string
        if (i == len) {
            new_str[i] = '\0';
        }
    }
    return new_str;
}

```

- プログラムの全体像

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t my_strlcpy(char *dst, const char *src, size_t size) {
    // get src length
    size_t src_len = strlen(src);
    // copy up to size - 1 characters from src to dst
    size_t actual_size = size - 1;
    for (size_t i = 0; i < actual_size; i++) {
        dst[i] = src[i];
    }
    // set null the end of the destination string
    dst[actual_size] = '\0';

    return src_len;
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    //  validate about creating malloc
    if (new_str == NULL) {
        return NULL;
    }
    // copy
    for (size_t i = 0; i <= len; i++) {
        new_str[i] = s[i];
        // set null the end of the new string
        if (i == len) {
            new_str[i] = '\0';
        }
    }
    return new_str;
}

#define BUF_SIZE 5000000
#define LOOP_SIZE 1000

int main(void) {
    //* Pre Process *//
    // 100_000
    char buffer[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++) {
        if (i == (BUF_SIZE - 1)) {
            buffer[i] = '\0';
        } else {
            buffer[i] = 'a';
        }
    }
    char s1[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++) {
        if (i == (BUF_SIZE - 1)) {
            s1[i] = '\0';
        } else {
            s1[i] = 'b';
        }
    }

    //* main process of strlcpy *//
    clock_t start_strlcpy_time, end_strlcpy_time;
    // start time
    start_strlcpy_time = clock();
    // main process of strlcpy
    for (int i = 0; i < LOOP_SIZE; i++) {
        // copy s1 to buffer
        strlcpy(buffer, s1, BUF_SIZE);
    }
    // end time
    end_strlcpy_time = clock();

    // result
    clock_t elapsed_strlcpy_time = end_strlcpy_time - start_strlcpy_time;
    fprintf(stdout, "strlcpy time: %f\n",
            (double)elapsed_strlcpy_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of strlcpy time: %f\n",
            (double)elapsed_strlcpy_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of my_strlcpy *//
    clock_t start_my_strlcpy_time, end_my_strlcpy_time;
    // start time
    start_my_strlcpy_time = clock();
    // main process of my_strlcpy
    for (int i = 0; i < LOOP_SIZE; i++) {
        // copy s1 to buffer
        my_strlcpy(buffer, s1, BUF_SIZE);
    }
    // end time
    end_my_strlcpy_time = clock();

    // result
    clock_t elapsed_my_strlcpy_time =
        end_my_strlcpy_time - start_my_strlcpy_time;
    fprintf(stdout, "my_strlcpy time: %f\n",
            (double)elapsed_my_strlcpy_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of my_strlcpy time: %f\n",
            (double)elapsed_my_strlcpy_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of strdup *//
    clock_t start_strdup_time, end_strdup_time;
    // start time
    start_strdup_time = clock();
    // main process of strdup
    for (int i = 0; i < LOOP_SIZE; i++) {
        char *s2 = strdup(s1);
        if (s2 == NULL) {
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        free(s2);
    }
    // end time
    end_strdup_time = clock();

    // result
    clock_t elapsed_strdup_time = end_strdup_time - start_strdup_time;
    fprintf(stdout, "strdup time: %f\n",
            (double)elapsed_strdup_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of strdup time: %f\n",
            (double)elapsed_strdup_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of my_strdup *//
    clock_t start_my_strdup_time, end_my_strdup_time;
    // start time
    start_my_strdup_time = clock();
    // main process of my_strdup
    for (int i = 0; i < LOOP_SIZE; i++) {
        char *s2 = my_strdup(s1);
        if (s2 == NULL) {
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        free(s2);
    }
    // end time
    end_my_strdup_time = clock();

    // result
    clock_t elapsed_my_strdup_time = end_my_strdup_time - start_my_strdup_time;
    fprintf(stdout, "my_strdup time: %f\n",
            (double)elapsed_my_strdup_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of my_strdup time: %f\n",
            (double)elapsed_my_strdup_time / CLOCKS_PER_SEC / LOOP_SIZE);

    return 0;
}

```

---
