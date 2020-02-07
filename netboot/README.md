# Raspberry Pi 3 network boot

Raspberry Pi 3でBareMetalなプログラムをネットワーク経由でブートできるようにします。

プログラムをリビルドするたびにプログラムをSDカードに書き込む必要がなくなり、開発が容易になります。

## 注意

こちらに記した情報は 2019/06/13 に動作確認を行いました。
今後の仕様変更でこの方法が利用できなくなる場合もありますので、ご注意ください。


## 準備

### Mac

Macではgnu-sedとvagrant、そして仮想マシンバックエンドにvirtualboxが必要になります。
homebrewなどを利用してインストールを行ってください。

```
brew install gnu-sed vagrant
brew cask install virtualbox
```

### Linux

Linuxの方はそれぞれの環境でvagrant及びVirtualboxのインストールを行ってください（libvirtバックエンドでも動作するはずですが、未検証です）。


## セットアップ

### USB bootの有効化

Raspberry PiのSDカードのbootパーティションにある `config.txt` に以下の1行を追記して、Raspberry Piの電源を入れ直してください。

```
program_usb_boot_mode=1
```

Raspberry Piの電源を入れて数秒後に電源を落とし、`config.txt` に追記した行を削除してください。


### firmware binaryのダウンロード

network bootに必要なバイナリファイルをダウンロードします。
`setup.sh` スクリプトを実行して、ダウンロードを行ってください。

```
./setup.sh
```

成功すればtftpbootディレクトリにダウンロードしたファイルが置かれます。

```
❯❯❯ tree -L 1 tftpboot
tftpboot
├── LICENCE.broadcom
├── bootcode.bin
├── fixup.dat
├── fixup_cd.dat
├── fixup_db.dat
├── fixup_x.dat
├── start.elf
├── start_cd.elf
├── start_db.elf
└── start_x.elf

0 directories, 10 files
```

### config.txtとkernel.imgの設置

起動したいプログラム(`kernel.img`)と`config.txt`を一緒に`tftpboot`ディレクトリ以下に設置してください。

### bootcode.binのコピー(Raspberry Pi 3 B+は不要)

Raspberry PiのSDカードのbootパーティションにあるファイルを全て削除し、`tftpboot`ディレクトリ以下にある `bootcode.bin` だけをSDカードのbootパーティションに入れてください。

### 設定ファイルの編集

ネットワークブートしたいRaspberry Piを、DHCPサーバーのあるネットワークに繋ぐ場合は「DHCP proxyサーバーとして使う設定」を参照してください。

そうでない場合、例えばパソコンのNICとRaspberry PiのNICを直結しているような、DHCPサーバーが無い環境などには「DHCPサーバーとして使う設定」を参照してください。

#### DHCP proxyサーバーとして使う設定

dnsmasqのDHPC proxy機能を持ちいて、ネットワークブートに必要な設定を既存のDHCPリクエストに加えてRaspberry Piに教えてあげるようにします。

`files/dnsmasq.conf` を開き、中身を次のようにすべて書き換えてください。

```
port=0
dhcp-range=192.168.111.255,proxy
log-dhcp
enable-tftp
tftp-root=/var/lib/tftpboot 
pxe-service=0,"Raspberry Pi Boot"
```

`192.168.111.255` の部分は利用するネットワークにあわせて編集してください。
例えば、パソコンにDHCPで振られるIPアドレスが `192.168.222.100` かつネットマスクが `255.255.255.0` の場合は `192.168.111.255` の部分を `192.168.222.255` に変更してください。

次に `Vagrantfile` を開き、public_networkの欄を以下のように書き換えて、DHCPサーバーのあるネットワークに接続しているNICを指定してください。

```
config.vm.network "public_network", bridge: "en1: Wi-Fi (AirPort)"
```

Virtualboxを仮想マシンのバックエンドにしている場合、設定できるNICの名前は以下のコマンドで確認が行なえます。

```
VBoxManage list bridgedifs |grep '^Name:'
```


#### DHCPサーバーとして使う設定

dnsmasqのDHPCサーバー機能を持ちいて、ネットワークブートに必要な設定をRaspberry Piに教えてあげるようにします。

まずは `files/dnsmasq.conf` を開き、中身を次のようにすべて書き換えてください。

```
port=0
dhcp-range=192.168.222.100,192.168.222.150,12h
log-dhcp
enable-tftp
# 3: disable default gateway
# 6: disable dns
dhcp-option=3
dhcp-option=6
tftp-root=/var/lib/tftpboot 
pxe-service=0,"Raspberry Pi Boot"
```

`dhcp-range=192.168.222.100,192.168.222.150,12h` の部分はDHCPサーバーが割り当てるアドレスレンジを設定しています。
他のNICが持つアドレスとかぶらないよう、設定を変更してください。


次に、vagrantを用いる場合は `Vagrantfile` を開いて、`public_network`の欄から利用するNICおよびNICのIPアドレスを設定してください。

例えば上の例の場合、vagrant側のNIC(今回はen1)には `192.168.222.1` などのIPアドレスを割り当てれば良いでしょう。

```
  config.vm.network "public_network", bridge: "en1: Wi-Fi (AirPort)", ip: "192.168.222.1"
```

Virtualboxを仮想マシンのバックエンドにしている場合、設定できるNICの名前は以下のコマンドで確認が行なえます。

```
VBoxManage list bridgedifs |grep '^Name:'
```



### 仮想マシンの起動

以下のコマンドを実行すると、ネットワークブートの環境が仮想マシン上で起動します。

```
vagrant up
```

## うまくいかないときは

Raspberry Piのシリアル出力及び仮想マシンのログを参照してください。

仮想マシン側のログは、仮想マシンに `vagrant ssh` コマンドでログインしたあと、`docker logs jpillora/dnsmasq` で確認できます。


## Reference

* https://www.raspberrypi.org/documentation/hardware/raspberrypi/bootmodes/net_tutorial.md