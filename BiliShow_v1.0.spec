# -*- mode: python ; coding: utf-8 -*-


block_cipher = None


a = Analysis(
    ['BiliShow_v1.0.py'],
    pathex=[],
    binaries=[],
   datas=[('Your python path/Lib/site-packages/onnxruntime/capi/onnxruntime_providers_shared.dll','onnxruntime\\capi'),('Your python path/Lib/site-packages/ddddocr/common_old.onnx','ddddocr'),('Your python path/Lib/site-packages/paddle','./paddle')],
    hiddenimports=['plyer.platforms','plyer.platforms.win','plyer.platforms.win.notification'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=block_cipher,
    noarchive=False,
)
for d in a.datas:
	if 'core_avx.pyd' in d[0]:
		a.datas.remove(d)
		break
pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.zipfiles,
    a.datas,
    [],
    name='BiliShow_v1.0',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
    icon=['icon_bilibili-square.ico'],
)
