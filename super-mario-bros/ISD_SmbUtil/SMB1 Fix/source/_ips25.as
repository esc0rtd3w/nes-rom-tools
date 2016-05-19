;###############################################################################
; IPS関連命令モジュール
	#module "IPS"
;###############################################################################

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
	if strsize>$40 : alloc outb,strsize
	bload p2,outb : outs=strsize
	return

;----------------------------------------
;	パッチングルーチン
;----------------------------------------
*p_patch
	p1a=5 : outa=0
	int ipl : ipl=0
	repeat
	  if p1a>=p1s : break					;ファイル終了
	  if outa>=outs : break					;ファイル終了
	  peek code,p1b,p1a : p1a++ : outa=code
	  peek code,p1b,p1a : p1a++ : outa=outa<<8+code
	  peek code,p1b,p1a : p1a++ : outa=outa<<8+code
	  if outa=$454F46 : break				;EOFは終了
	  peek code,p1b,p1a : p1a++ : ipl=code
	  peek code,p1b,p1a : p1a++ : ipl=ipl<<8+code
	  if ipl : gosub *p_sub1 : else : gosub *p_sub2		;RLE圧縮(ipl=0)の有無
	loop
	return
*p_sub1		;パッチサブ
	if outa+ipl>=outs : ipl=outs-outa
	repeat ipl
	  peek code,p1b,p1a : p1a++
	  poke outb,outa,code : outa++
	loop
	return
*p_sub2		;パッチサブ(RLE圧縮)
	peek code,p1b,p1a : p1a++ : ipl=code
	peek code,p1b,p1a : p1a++ : ipl=ipl<<8+code
	peek code,p1b,p1a : p1a++
	if outa+ipl>=outs : ipl=outs-outa
	repeat ipl
	  poke outb,outa,code : outa++
	loop
	return

;###############################################################################

	#deffunc ipsm val,val
	mref p1, 24		;変更前ファイル名
	mref p2, 25		;変更後ファイル名
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
	if p1s>p2s : outs=p2s : else : 	outs=p1s
	if outs>=$40 : alloc outb,outs+$0100
	return

;----------------------------------------
;	パッチ作成ルーチン
;----------------------------------------
*m_patch
	poke outb,$0000,"PATCH" : outa=5
	int ipl  : ipl=0
	int code : code=0
	repeat
	  code=p1a>>2
	  if p1a>=outs : break
	  if p1b.code = p2b.code : p1a+4 : else : gosub *m_sub1	;相違の有無
	loop
	poke outb,outa,"EOF" : outa+3
	outs=outa
	return
*m_sub1
	peek temp1,p1b,p1a : peek temp2,p2b,p1a
	if temp1=temp2 : p1a++ : return			;位置確認
	rle1=temp2

	poke outb,outa  ,p1a>>16
	poke outb,outa+1,p1a>>8
	poke outb,outa+2,p1a
	rle2=0						;RLEチェック用
	repeat
	  if p1a>=outs : ipl=cnt : break
	  peek temp1,p1b,p1a : peek temp2,p2b,p1a
	  if temp1=temp2 : ipl=cnt : break		;抜ける
	  if temp2=rle1 : rle2++			;RLEチェック
	  poke outb,outa+5+cnt,temp2
	  p1a++
	loop
	if ipl=rle2 : if ipl>2 : goto *m_sub2		;RLE圧縮する
	poke outb,outa+3,ipl>>8
	poke outb,outa+4,ipl
	outa+5+ipl
	return
*m_sub2		;RLE圧縮処理
	poke outb,outa+3,$00
	poke outb,outa+4,$00
	poke outb,outa+5,ipl>>8
	poke outb,outa+6,ipl
	poke outb,outa+7,rle1
	outa+8
	return

;###############################################################################

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
	p1a=5 : int ipl : ipl=0
	repeat
	  if p1a>=p1s : break					;ファイル終了
	  peek code,p1b,p1a : p1a++ : outa=code
	  peek code,p1b,p1a : p1a++ : outa=outa<<8+code
	  peek code,p1b,p1a : p1a++ : outa=outa<<8+code
	  if outa=$454F46 : break				;EOFは終了
	  peek code,p1b,p1a : p1a++ : ipl=code
	  peek code,p1b,p1a : p1a++ : ipl=ipl<<8+code
	  if ipl : p1a+ipl : else : p1a+3			;RLE圧縮(ipl=0)の有無
	loop
	return

;###############################################################################

	#deffunc ipss val
	mref p1,32		;ファイル名
	mref p0,64 : p0=0	;stat
	if p1="":p0=1:return
	if mode=0:p0=1:return	;失敗している時
	bsave p1,outb,outs
	return

;###############################################################################

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
	strlen ipl,p1 : ipl--
	repeat ipl
	  peek code,p1,ipl-cnt
	  if code=$2E  : strmid s0,p1,0,ipl-cnt : break
	  if code=$5C  : strmid s0,p1,0,ipl     : break
	  if cnt+1=ipl : strmid s0,p1,0,ipl     : break
	loop
	strlen ipl,p2 : ipl--
	repeat ipl
	  peek code,p2,ipl-cnt
	  if code=$2E  : strmid p9,p2,-1,cnt	: break
	  if code=$5C  : p9=""			: break
	  if cnt=ipl   : p9=""			: break
	loop
	s0+"."+p9
	instr code,s0,":" : if code=-1 : s0=curdir+"\\"+s0	;相対パスでのファイル指定
	return

*m_getname	;合成出力名"変更後のファイル名.ips"
	mref s0,65 : s0=""	;refstr
	strlen ipl,p2 : ipl--
	repeat ipl
	  peek code,p2,ipl-cnt
	  if code=$2E  : strmid s0,p2,0,ipl-cnt : break
	  if code=$5C  : strmid s0,p2,0,ipl     : break
	  if cnt+1=ipl : strmid s0,p2,0,ipl     : break
	loop
	s0+".ips"
	instr code,s0,":" : if code=-1 : s0=curdir+"\\"+s0	;相対パスでのファイル指定
	return

;###############################################################################
	#global
;###############################################################################

