	#include "_ips25.as"
	#include "_ex.as"

	;初期化
	ipsf="smb_fix.ips"				;正常化パッチ
	sdim  romf,$0200  : sdim  fixf,$0200		;ファイル名
	alloc romb,$18000

	bgscr 2,1,1,1,-1,-1 : title "SMB-FIX" : gsel 2,1

	;ファイルを開く
	if cmdline="" {
	  dialog "nes",16,"SMB ROM image"
	  if stat!1 : end
	  romf=refstr
	} else {
	  romf=cmdline					;コマンドラインが指定されている
	}

	;小さすぎるファイルサイズをチェック
	exist romf : roms=strsize
	if roms<$4010 : goto *error_bad_rom

	;ヘッダチェック
	bload romf,romb,$10
	peek code,romb,$0004				;PRG-ROM数
	if code!2 : goto *error_bad_rom
	peek code,romb,$0005				;CHR-ROM数
	if code!1 : goto *error_bad_rom
	peek code,romb,$0006				;トレイナー
	if code&4 : addr=$0210 : else : addr=$0010

	;バックアップ作成
	fixf=romf
	dex fixf
	pex fixf,"bak"
	bload romf,romb,roms
	bsave fixf,romb,roms

	;トレイナーを排除/サイズ調整
	bload fixf,romb,$0010,$0000			;ヘッダを保存
	bsave romf,romb,$0010
	bload fixf,romb,$A000,addr			;ROMを保存
	bsave romf,romb,$A000,$0010

	;正常化パッチを当てる
	ipsp ipsf,romf
	if stat!0 : dialog "Fix error",,"ERROR" : end
	ipss romf
	if stat!0 : dialog "Output error",,"ERROR" : end
	end

*error_bad_rom
	dialog "The file isn't SMB ROM image.",,"ERROR"
	end
