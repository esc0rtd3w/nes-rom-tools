;#######################################
; IPS関連命令モジュール for HSP v2.6
	#module "IPS"
;#######################################

	#deffunc ipsp val,val
	mref p1,24		;IPSファイル名
	mref p2,25		;対象ファイル名
	mref p0,64 : p0=0	;stat
	if p1="":p0=1:return
	if p2="":p0=1:return

	mode=0
	gosub *p_fload		;ファイル読込み
	if p0!0:return
	gosub *p_patch		;パッチング
	if p0=1:return
	mode=1
	gosub *p_getname	;refstrに合成名を入れる
	return

;----------------------------------------
;	ファイル読込み
;----------------------------------------
*p_fload
	;IPSファイル
	exist p1 : if strsize<1 : p0=1 : return
	if strsize>$40 : alloc p1b,strsize
	bload p1,p1b : p1s=strsize
	gosub *chk_ips			;IPS簡易チェック
	;対象ファイル
	exist p2 : if strsize<1 : p0=1 : return
	if strsize>$40 : alloc otb,strsize
	bload p2,otb : ots=strsize
	return

;----------------------------------------
;	パッチングルーチン
;----------------------------------------
*p_patch
	p1a=5 : ota=0 : len=0
	repeat
	  if p1a>=p1s : break					;IPSファイル終了
	  if ota>=ots : break					;対象ファイル終了
	  peek code,p1b,p1a : p1a++ : ota=code
	  peek code,p1b,p1a : p1a++ : ota=ota<<8+code
	  peek code,p1b,p1a : p1a++ : ota=ota<<8+code
	  if ota=$454F46 : break				;EOFは終了
	  peek code,p1b,p1a : p1a++ : len=code
	  peek code,p1b,p1a : p1a++ : len=len<<8+code
	  if len : gosub *p_sub1 : else : gosub *p_sub2		;RLE圧縮(len=0)の有無
	loop
	return

*p_sub1		;(標準)パッチ
	if ota+len>=ots : len=ots-ota
	memcpy otb,p1b,len,ota,p1a : p1a+len
	return

*p_sub2		;(圧縮)パッチ
	peek code,p1b,p1a : p1a++ : len=code
	peek code,p1b,p1a : p1a++ : len=len<<8+code
	peek code,p1b,p1a : p1a++
	if ota+len>=ots : len=ots-ota
	memset otb,code,len,ota
	return

;#######################################

	#deffunc ipsm val,val
	mref p1,24		;変更前ファイル名
	mref p2,25		;変更後ファイル名
	mref p0,64 : p0=0	;stat
	if p1="":p0=1:return
	if p2="":p0=1:return

	mode=0
	gosub *m_fload		;ファイル読込み
	if p0!0:return
	gosub *m_patch		;パッチング
	if p0=1:return
	mode=1
	gosub *m_getname	;refstrに合成名を入れる
	return

;----------------------------------------
;	ファイル読込み
;----------------------------------------
*m_fload
	;変更前ファイル名
	exist p1 : if strsize<1 : p0=1 : return
	if strsize>$40 : alloc p1b,strsize+4
	bload p1,p1b : p1s=strsize
	;変更後ファイル名
	exist p2 : if strsize<1 : p0=1 : return
	if strsize>$40 : alloc p2b,strsize+4
	bload p2,p2b : p2s=strsize
	;比較するファイルのサイズチェックとIPSファイルバッファ取得
	if p1s>p2s : ots=p2s : else : ots=p1s
	if ots>=$40 : alloc otb,ots+$1000
	return

;----------------------------------------
;	パッチ作成ルーチン
;----------------------------------------
*m_patch
	poke otb,$0000,"PATCH" : ota=5
	code=0 : len=0 : p2a=0
	repeat
	  code=p1a>>2
	  if p1a>=ots : break					;小さい方のファイルの終了
	  if p1b.code = p2b.code : p1a+4 : else : gosub *m_sub1	;相違の有無
	loop
	poke otb,ota,"EOF" : ota+3
	ots=ota
	return

*m_sub1		;相違を発見
	peek temp1,p1b,p1a : peek temp2,p2b,p1a
	if temp1=temp2 : p1a++ : return			;位置確認
	rle1=temp2

	;アドレスを記録
	poke otb,ota  ,p1a>>16
	poke otb,ota+1,p1a>>8
	poke otb,ota+2,p1a
	p2a=p1a

	rle2=0						;RLEチェック用
	repeat
	  if p1a>=ots : len=cnt : break
	  peek temp1,p1b,p1a : peek temp2,p2b,p1a
	  if temp1=temp2 : len=cnt : break
	  if temp2=rle1 : rle2++			;RLEチェック
;	  poke otb,ota+5+cnt,temp2
	  p1a++
	loop
	if len=rle2 : if len>2 : goto *m_sub2		;RLE圧縮の処理
	poke otb,ota+3,len>>8
	poke otb,ota+4,len
	memcpy otb,p2b,len,ota+5,p2a
	ota+5+len
	return

*m_sub2
	;RLE圧縮で記録
	poke otb,ota+3,$00
	poke otb,ota+4,$00
	poke otb,ota+5,len>>8
	poke otb,ota+6,len
	poke otb,ota+7,rle1
	ota+8
	return

;#######################################

	#deffunc ipsc val
	mref p1,24		;IPSファイル名
	mref p0,64 : p0=0	;stat
	if p1="":p0=1:return

	;IPSファイルを読込む
	exist p1 : if strsize<1 : p0=1 : return
	if strsize>$40 : alloc p1b,strsize
	bload p1,p1b : p1s=strsize
	gosub *chk_ips			;IPS簡易チェック
	if p0!0:return

	gosub *c_patch			;チェックルーチン
	if p0!0:return
	return

;----------------------------------------
;	チェックルーチン
;----------------------------------------
*c_patch
	p1a=5 : len=0
	repeat
	  if p1a>=p1s : break					;ファイル終了
	  peek code,p1b,p1a : p1a++ : ota=code
	  peek code,p1b,p1a : p1a++ : ota=ota<<8+code
	  peek code,p1b,p1a : p1a++ : ota=ota<<8+code
	  if ota=$454F46 : break				;EOFは終了
	  peek code,p1b,p1a : p1a++ : len=code
	  peek code,p1b,p1a : p1a++ : len=len<<8+code
	  if len : p1a+len : else : p1a+3			;RLE圧縮(len=0)の有無
	loop
	return

;#######################################

	#deffunc ipss val
	mref p1,32		;ファイル名
	mref p0,64 : p0=0	;stat
	if p1="" :p0=1:return
	if mode=0:p0=1:return	;失敗している時
	bsave p1,otb,ots
	return

;#######################################

*chk_ips	;IPS簡易チェックルーチン
	str temp : temp=""
	strmid temp,p1b,0,5		;PATCH
	if temp!"PATCH" : p0=1 : return
	strmid temp,p1b,p1s-3,3		;EOF
	if temp!"EOF"   : p0=1 : return
	return

*p_getname	;合成出力名"IPSファイル名.対象拡張子"
	sdim p9,64 : p9=""
	mref s0,65 : s0=""	;refstr
	strlen len,p1 : len--
	repeat len
	  peek code,p1,len-cnt
	  if code=$2E  : strmid s0,p1,0,len-cnt : break
	  if code=$5C  : strmid s0,p1,0,len     : break
	  if cnt+1=len : strmid s0,p1,0,len     : break
	loop
	strlen len,p2 : len--
	repeat len
	  peek code,p2,len-cnt
	  if code=$2E  : strmid p9,p2,-1,cnt	: break
	  if code=$5C  : p9=""			: break
	  if cnt=len   : p9=""			: break
	loop
	s0+"."+p9
	instr code,s0,":" : if code=-1 : s0=curdir+"\\"+s0	;相対パスでのファイル指定
	return

*m_getname	;合成出力名"変更後のファイル名.ips"
	mref s0,65 : s0=""	;refstr
	strlen len,p2 : len--
	repeat len
	  peek code,p2,len-cnt
	  if code=$2E  : strmid s0,p2,0,len-cnt : break
	  if code=$5C  : strmid s0,p2,0,len     : break
	  if cnt+1=len : strmid s0,p2,0,len     : break
	loop
	s0+".ips"
	instr code,s0,":" : if code=-1 : s0=curdir+"\\"+s0	;相対パスでのファイル指定
	return

;#######################################
	#global
;#######################################
