属性エラー情報ＦＴＰ取得処理
○概要
・基幹システムの属性ファイルを取得し、その中から属性修正レコードのみ抽出して処理用ファイルを作成している。
  通常は LD103 から設定時間毎に起動される。

・lftpコマンドのmirrorを用いて、基幹システムのディレクトリに存在し、ローカル(shusei/tmp)に存在しないファイルを全て取得する。
  取得が終わった後に、前回処理ファイル(~/bin/LD102_Log/ 内に存在) 以降に取得したファイルを処理する。

○注意点
・lftpコマンドのmirrorでは、ファイル作成日付の秒が切り捨てられてしまうことが判明した。
  また、find コマンドの newer オプションでは同一の作成日時のファイルは取得できない。
  そのため、ファイル作成日時−１秒を算出し、その時刻より新しく作成されたファイルを newermt オプションで検索している。

・ただし、これだけだとすでに処理したファイルが再度処理対象となってしまうため、
  newercc オプションを使用して、最終ステータス変更時刻 (ctime) -- FTP で取得した時刻 でも比較している。

・newercc オプションだけにすると、もし古いファイルを再取得した場合等に再び再処理してしまうため、
  newermt と newercc の両方をセットにして対象を絞っている。
  (祝日等でホスト側が古いファイルの削除をスキップした場合など、古いファイルを再取得する可能性は存在する。)

・もし、取得漏れが発生した場合は、shusei/tmp のファイルを手動で shusei ディレクトリに移動してあげれば、
  このシェルが起動した際に、再処理をしてくれる。
