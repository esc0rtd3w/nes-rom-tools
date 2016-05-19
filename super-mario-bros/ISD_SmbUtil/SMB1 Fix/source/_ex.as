;===============================================================
; Šg’£q‘€ìƒ‚ƒWƒ…[ƒ‹  by ‚í‚¢‚í‚¢ (geo-yy@geocities.co.jp)
;===============================================================

	#module "EXT"

;===============================================================
;	pex p1,p2	: Šg’£q‚ğ’Ç‰Á‚·‚é
;		p1	: Šg’£q‚ğ’Ç‰Á‚·‚é•¶š—ñ•Ï”
;		p2	: ’Ç‰Á‚·‚éŠg’£q
;		stat	: ¬Œ÷=0A¸”s=1

	#deffunc pex val,str
	mref p1,24
	mref p2,33
	mref p0,64 : p0=0
	if p2="":p0=1:return

	int code:int temp:strlen temp,p2:temp--
	peek code,p2,0		;’Ç‰ÁŠg’£q‚Ì1•¶š–Ú‚ª"."‚Ìê‡‚Íæ‚é
	if code='.':strmid p2,p2,1,temp

	if p1="":p0=1:return
	if p2="":p0=1:return

	int code:int temp:strlen temp,p1:temp--
	repeat temp
	    peek code,p1,temp-cnt
	    if code='.'&(cnt=0):p1=p1+""+p2:break
	    if code='.':break
	    if code='\':p1=p1+"."+p2:break
	loop
	p0=0
	return

;===============================================================
;	gex p1,p2	: Šg’£q‚ğæ“¾‚·‚é
;		p1	: æ“¾‚µ‚½Šg’£q‚ğŠi”[‚·‚é•¶š—ñ•Ï”
;		p2	: Šg’£q‚ğæ“¾‚·‚é•¶š—ñ•Ï”
;		stat	: ¬Œ÷=0A¸”s=1

	#deffunc gex val,val
	mref p1, 24 : p1=""
	mref p2, 25
	mref p0, 64 : p0=0
	if p2="":p0=1:return

	int code:int temp:strlen temp,p2:temp--
	repeat temp
	    peek code,p2,temp-cnt
	    if code='.' : strmid p1,p2,-1,cnt	: break
	    if code='\' : gosub *chk_dir	: break
	loop
	p0=0
	return
*chk_dir
	if cnt=0:p1="\\":return
	dirlist p2,p2,5
	if stat=1:p1="\\"
	if stat=0:p1=""
	return

;===============================================================
;	dex p1		: Šg’£q‚ğíœ‚·‚é
;		p1	: Šg’£q‚ğíœ‚·‚é•¶š—ñ•Ï”
;		stat	: ¬Œ÷=0A¸”s=1

	#deffunc dex val
	mref p1, 24
	mref p0, 64 : p0=0
	if p1="":p0=1:return

	int code:int temp:strlen temp,p1:temp--
	repeat temp
	    peek code,p1,temp-cnt
	    if code='.' : strmid p1,p1,0,temp-cnt	: break
	    if code='\' :	: break
	loop
	p0=0
	return

	#global

;===============================================================

