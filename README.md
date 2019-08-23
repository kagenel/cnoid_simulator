# cnoid_simulator
簡単な BodyRTC と BodyIoRTC によるトルク制御．
----------------
BodyRTC と BodyIoRTC の cmake や choreonoid によるシミュレーションまでの一通りの動作を確認した．

制御は関節にトルクを投げただけのやつなので主に choreonoid の勉強用．

src の内容は以下の通り．

- BodyRTC用
sampleRTC.h，sampleRTC.cpp，sampleRTC3R.conf

- BodyIoRTC用
sampleIoRTC.cpp

どちらも一緒に`/build/bin/`内に共有ライブラリとして一緒にビルドされるが BodyRTC に使うには名前を SampleIoRTC.so から
SampleRTC.so に変更する必要がある．
