InterfaceのP22のLチカプログラムはうまく動きました。
C言語もLinux OSも初めてで、コンパイル、ビルドとかに関してもよくわからずでしたが、なんとかできました。
InterfaceのPDFはコピペできないように制限がかかっているので、手打ちでコード書きました。
Ras-Piの上で手打ちは良いIDEすぐには見つからなくて厳しかったので、Mac上でCLion（アカデミックのemailアドレスで無料で使えます）というIDEで編集してGitHubにpush後
Ras-Pi上のローカルにcloneしてコンパイルしました。デバッグが面倒で、IDE上だけで完結できればいいのですが、、
最初コンパイルしたとき、ライブラリの読み込みで　"lib/libusbdrdaq.so.2"が見つからないぞと怒られました。
ただドライバをインストールし直してビルドしたらエラーや警告なく実行ファイルが生成されました。
その後ファイルを実行すると最初のif文で引っかかってunable to open Dr DAQ deviceのメッセージが返ってきたのですが、
もう一度ビルドし直して実行するとよくわからんですがちゃんとLチカできました。
gitでhistory見ても基本的に同じなのにどこで引っかかたんだろうか。。。？



githubのメーカー提供のコードはInterfaceの通りに修正しても、ビルドすると警告が返ってきます。

```
pi@raspberrypi:~ $ gcc usbdrdaqCon.c -I/opt/picoscope/include -L/opt/picoscope/lib -lusbdrdaq -o usbdrdaqCon
```

```
usbdrdaqCon.c: In function ‘channelScaling’:
usbdrdaqCon.c:934:18: warning: comparison between pointer and integer
  while (names[i] != NULL)
                  ^~
usbdrdaqCon.c:942:44: warning: comparison between pointer and integer
    if (i < (namesSize - 1) && names[i + 1] != NULL)
                                            ^~
usbdrdaqCon.c:961:8: warning: implicit declaration of function ‘toupper’ [-Wimplicit-function-declaration]
   ch = toupper(_getch());
        ^~~~~~~
```

`toupper`関数が宣言されていません警告は
`#include <ctype.h>`
の一行を追加することでなくなりました。

残り２つのint型とポインタ型を比較しているぞ警告は、
すぐにはわからなかったのでとりあえず放置して実行すると
LED点灯プログラムは走っていました。
それ以外はまだチェックしてないです。