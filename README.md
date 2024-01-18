# ev3rt
### linemonの動作不備
- linetracer_run()を実行しても走り出さないので、検証したところ、
linemon_is_onlineが線を認識していないことが原因だと分かった。原因究明中。
- なんと組み立ての際にcolor_sensorを別の部品と間違えていた。それは動くわけない。
- while文でループ処理することで走行が可能になった。