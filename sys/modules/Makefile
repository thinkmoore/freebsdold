# $FreeBSD: stable/9/sys/modules/Makefile 253836 2013-07-31 11:36:20Z marius $

.include <bsd.own.mk>

# Modules that include binary-only blobs of microcode should be selectable by
# MK_SOURCELESS_UCODE option (see below).

SUBDIR=	\
	${_3dfx} \
	${_3dfx_linux} \
	${_aac} \
	${_aacraid} \
	accf_data \
	accf_dns \
	accf_http \
	${_acpi} \
	ae \
	${_aesni} \
	age \
	${_agp} \
	aha \
	${_ahb} \
	ahci \
	${_aic} \
	aic7xxx \
	aio \
	alc \
	ale \
	alq \
	${_amd} \
	${_amdsbwd} \
	${_amdtemp} \
	amr \
	${_an} \
	${_aout} \
	${_apm} \
	${_arcmsr} \
	${_arcnet} \
	${_asmc} \
	${_asr} \
	ata \
	ath \
	ath_pci \
	${_auxio} \
	${_bce} \
	bfe \
	bge \
	${_bxe} \
	${_bios} \
	${_bktr} \
	${_bm} \
	bridgestp \
	bwi \
	bwn \
	cam \
	${_canbepm} \
	${_canbus} \
	${_cardbus} \
	cas \
	${_cbb} \
	cc \
	cd9660 \
	cd9660_iconv \
	${_ce} \
	${_ciss} \
	${_cm} \
	${_cmx} \
	coda \
	coda5 \
	${_coff} \
	${_coretemp} \
	${_cp} \
	${_cpuctl} \
	${_cpufreq} \
	${_crypto} \
	${_cryptodev} \
	${_cs} \
	${_ctau} \
	ctl \
	${_cxgb} \
	cxgbe \
	${_cyclic} \
	dc \
	dcons \
	dcons_crom \
	de \
	${_dpms} \
	${_dpt} \
	${_drm} \
	${_drm2} \
	${_dtrace} \
	dummynet \
	${_ed} \
	${_elink} \
	${_em} \
	en \
	${_ep} \
	${_epic} \
	esp \
	${_et} \
	${_ex} \
	${_exca} \
	${_ext2fs} \
	${_fatm} \
	fdc \
	fdescfs \
	${_fe} \
	${_filemon} \
	firewire \
	firmware \
	${_fxp} \
	gem \
	geom \
	${_glxiic} \
	${_glxsb} \
	hatm \
	hifn \
	hme \
	${_hpt27xx} \
	${_hptiop} \
	${_hptmv} \
	${_hptnr} \
	${_hptrr} \
	hwpmc \
	${_i2c} \
	${_ibcs2} \
	${_ichwd} \
	${_ida} \
	${_ie} \
	if_bridge \
	${_if_carp} \
	if_disc \
	if_edsc \
	if_ef \
	if_epair \
	if_faith \
	if_gif \
	${_if_gre} \
	if_lagg \
	${_if_ndis} \
	if_stf \
	if_tap \
	if_tun \
	if_vlan \
	${_igb} \
	${_iir} \
	${_io} \
	ipdivert \
	${_ipfilter} \
	${_ipfw} \
	ipfw_nat \
	${_ipmi} \
	ip6_mroute_mod \
	ip_mroute_mod \
	${_ips} \
	${_ipw} \
	${_ipwfw} \
	${_isci} \
	iscsi \
	isp \
	${_ispfw} \
	${_iwi} \
	${_iwifw} \
	${_iwn} \
	${_iwnfw} \
	${_ixgb} \
	${_ixgbe} \
	jme \
	joy \
	kbdmux \
	kgssapi \
	kgssapi_krb5 \
	khelp \
	krpc \
	ksyms \
	le \
	lge \
	libalias \
	libiconv \
	libmbpool \
	libmchain \
	${_lindev} \
	${_linprocfs} \
	${_linsysfs} \
	${_linux} \
	lmc \
	lpt \
	mac_biba \
	mac_bsdextended \
	mac_ifoff \
	mac_lomac \
	mac_mls \
	mac_none \
	mac_partition \
	mac_portacl \
	mac_seeotheruids \
	mac_stub \
	mac_test \
	malo \
	mcd \
	md \
	mem \
	mfi \
	mii \
	mlx \
	${_mlx4} \
	${_mlx4ib} \
	${_mlxen} \
	${_mly} \
	mmc \
	mmcsd \
	mps \
	mpt \
	mqueue \
	msdosfs \
	msdosfs_iconv \
	${_mse} \
	msk \
	${_mthca} \
	mvs \
	mwl \
	${_mwlfw} \
	mxge \
	my \
	${_ncp} \
	${_ncv} \
	${_ndis} \
	${_netgraph} \
	${_nfe} \
	nfs_common \
	nfscl \
	nfsclient \
	nfscommon \
	nfsd \
	nfslock \
	nfslockd \
	nfsserver \
	nfssvc \
	nge \
	nmdm \
	${_nsp} \
	ntfs \
	ntfs_iconv \
	nullfs \
	${_nvd} \
	${_nve} \
	${_nvme} \
	${_nvram} \
	${_nwfs} \
	${_nxge} \
	${_opensolaris} \
	oce \
	${_padlock} \
	patm \
	${_pccard} \
	${_pcfclock} \
	pcn \
	${_pf} \
	${_pflog} \
	${_pfsync} \
	plip \
	${_pmc} \
	portalfs \
	ppbus \
	ppc \
	ppi \
	pps \
	procfs \
	pseudofs \
	${_pst} \
	pty  \
	puc \
	${_qlxgb} \
	ral \
	${_ralfw} \
	${_random} \
	rc4 \
	${_rdma} \
	re \
	reiserfs \
	rl \
	${_runfw} \
	${_s3} \
	${_safe} \
	${_sbni} \
	scc \
	scd \
	${_scsi_low} \
	sdhci \
	sem \
	send \
	${_sf} \
	${_sfxge} \
	sge \
	siba_bwn \
	siftr \
	siis \
	sis \
	sk \
	${_smbfs} \
	${_sn} \
	${_snc} \
	snp \
	${_sound} \
	${_speaker} \
	${_splash} \
	${_sppp} \
	ste \
	${_stg} \
	stge \
	${_streams} \
	${_svr4} \
	${_sym} \
	${_syscons} \
	sysvipc \
	${_ti} \
	tl \
	tmpfs \
	${_toecore} \
	${_tpm} \
	trm \
	${_twa} \
	twe \
	tws \
	tx \
	${_txp} \
	uart \
	ubsec \
	udf \
	udf_iconv \
	ufs \
	unionfs \
	usb \
	utopia \
	${_vesa} \
	${_virtio} \
	vge \
	${_viawd} \
	vkbd \
	${_vpo} \
	vr \
	vte \
	vx \
	${_vxge} \
	wb \
	${_wbwd} \
	${_wi} \
	wlan \
	wlan_acl \
	wlan_amrr \
	wlan_ccmp \
	wlan_rssadapt \
	wlan_tkip \
	wlan_wep \
	wlan_xauth \
	${_wpi} \
	${_wpifw} \
	${_x86bios} \
	${_xe} \
	xfs \
	xl \
	${_zfs} \
	zlib \

.if ${MACHINE_CPUARCH} == "i386" || ${MACHINE_CPUARCH} == "amd64"
_filemon=	filemon
.endif

.if ${MACHINE_CPUARCH} != "powerpc" && ${MACHINE_CPUARCH} != "arm" && \
	${MACHINE_CPUARCH} != "mips"
_syscons=	syscons
_vpo=		vpo
.endif

.if ${MACHINE_CPUARCH} != "arm" && ${MACHINE_CPUARCH} != "mips"
# no BUS_SPACE_UNSPECIFIED
# No barrier instruction support (specific to this driver)
_sym=		sym
# intr_disable() is a macro, causes problems
.if ${MK_SOURCELESS_UCODE} != "no"
_cxgb=		cxgb
.endif
.endif

.if ${MK_CRYPT} != "no" || defined(ALL_MODULES)
.if exists(${.CURDIR}/../opencrypto)
_crypto=	crypto
_cryptodev=	cryptodev
.endif
.if exists(${.CURDIR}/../crypto)
_random=	random
.endif
.endif

.if ${MK_INET_SUPPORT} != "no" || defined(ALL_MODULES)
_if_gre=	if_gre
.endif

.if (${MK_INET_SUPPORT} != "no" || ${MK_INET6_SUPPORT} != "no") || \
	defined(ALL_MODULES)
_if_carp=	if_carp
_toecore=	toecore
.endif

.if ${MK_IPFILTER} != "no" || defined(ALL_MODULES)
_ipfilter=	ipfilter
.endif

.if ${MK_INET_SUPPORT} != "no" || defined(ALL_MODULES)
_ipfw=		ipfw
.endif

.if ${MK_NETGRAPH} != "no" || defined(ALL_MODULES)
_netgraph=	netgraph
.endif

.if (${MK_PF} != "no" && (${MK_INET_SUPPORT} != "no" || \
	${MK_INET6_SUPPORT} != "no")) || defined(ALL_MODULES)
_pf=		pf
_pflog=		pflog
.if ${MK_INET_SUPPORT} != "no"
_pfsync=	pfsync
.endif
.endif

.if ${MK_SOURCELESS_UCODE} != "no"
_bce=		bce
_fatm=		fatm
_fxp=		fxp
_ispfw=		ispfw
_mwlfw=		mwlfw
_ralfw=		ralfw
_runfw=		runfw
_sf=		sf
_sn=		sn
_ti=		ti
_txp=		txp
.endif

.if ${MACHINE_CPUARCH} == "i386"
# XXX some of these can move to the general case when de-i386'ed
# XXX some of these can move now, but are untested on other architectures.
_3dfx=		3dfx
_3dfx_linux=	3dfx_linux
_agp=		agp
_aic=		aic
_amd=		amd
_an=		an
_aout=		aout
_apm=		apm
_arcnet=	arcnet
_bktr=		bktr
_bxe=		bxe
_cardbus=	cardbus
_cbb=		cbb
.if ${MK_SOURCELESS_UCODE} != "no"
_ce=		ce
.endif
_coff=		coff
.if ${MK_SOURCELESS_UCODE} != "no"
_cp=		cp
.endif
_cpuctl=	cpuctl
_cpufreq=	cpufreq
_cs=		cs
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_cyclic=	cyclic
.endif
_dpms=		dpms
_drm=		drm
_drm2=		drm2
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_dtrace=	dtrace
.endif
_ed=		ed
_elink=		elink
_em=		em
_ep=		ep
_et=		et
_exca=		exca
_ext2fs=	ext2fs
_fe=		fe
_glxiic=	glxiic
_glxsb=		glxsb
_i2c=		i2c
_ibcs2=		ibcs2
_ie=		ie
_if_ndis=	if_ndis
_igb=		igb
_io=		io
_lindev=	lindev
_linprocfs=	linprocfs
_linsysfs=	linsysfs
_linux=		linux
_mse=		mse
.if ${MK_OFED} != "no" || defined(ALL_MODULES)
_mlx4=		mlx4
_mlx4ib=	mlx4ib
_mlxen=		mlxen
_mthca=		mthca
.endif
.if ${MK_NCP} != "no"
_ncp=		ncp
.endif
_ncv=		ncv
_ndis=		ndis
_nsp=		nsp
.if ${MK_NCP} != "no"
_nwfs=		nwfs
.endif
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_opensolaris=	opensolaris
.endif
_pccard=	pccard
_pcfclock=	pcfclock
_pst=		pst
_rdma=		rdma
_safe=		safe
_sbni=		sbni
_scsi_low=	scsi_low
_smbfs=		smbfs
_sound=		sound
_speaker=	speaker
_splash=	splash
_sppp=		sppp
_stg=		stg
_streams=	streams
_svr4=		svr4
_vxge=  	vxge
_wbwd=		wbwd
_wi=		wi
_xe=		xe
.if ${MK_ZFS} != "no" || defined(ALL_MODULES)
_zfs=		zfs
.endif
.if ${MACHINE} == "i386"
_aac=		aac
_aacraid=	aacraid
_acpi=		acpi
.if ${MK_CRYPT} != "no" || defined(ALL_MODULES)
_aesni=		aesni
.endif
_ahb=		ahb
_amdsbwd=	amdsbwd
_amdtemp=	amdtemp
_arcmsr=	arcmsr
_asmc=		asmc
_asr=		asr
_bios=		bios
_ciss=		ciss
_cm=		cm
_cmx=		cmx
_coretemp=	coretemp
.if ${MK_SOURCELESS_UCODE} != "no"
_ctau=		ctau
.endif
_dpt=		dpt
_ex=		ex
.if ${MK_SOURCELESS_HOST} != "no"
_hpt27xx=	hpt27xx
.endif
_hptiop=	hptiop
.if ${MK_SOURCELESS_HOST} != "no"
_hptmv=		hptmv
_hptnr=		hptnr
_hptrr=		hptrr
.endif
_ichwd=		ichwd
_ida=		ida
_iir=		iir
_ipmi=		ipmi
_ips=		ips
_ipw=		ipw
.if ${MK_SOURCELESS_UCODE} != "no"
_ipwfw=		ipwfw
.endif
_isci=		isci
_iwi=		iwi
.if ${MK_SOURCELESS_UCODE} != "no"
_iwifw=		iwifw
.endif
_iwn=		iwn
.if ${MK_SOURCELESS_UCODE} != "no"
_iwnfw=		iwnfw
.endif
_ixgb=		ixgb
_ixgbe=		ixgbe
_mly=		mly
_nfe=		nfe
_nvd=		nvd
.if ${MK_SOURCELESS_HOST} != "no"
_nve=		nve
.endif
_nvme=		nvme
_nvram=		nvram
_nxge=		nxge
_tpm=		tpm
_viawd=		viawd
_wpi=		wpi
.if ${MK_SOURCELESS_UCODE} != "no"
_wpifw=		wpifw
.endif
.if ${MK_CRYPT} != "no" || defined(ALL_MODULES)
_padlock=	padlock
.endif
_s3=		s3
_twa=		twa
_vesa=		vesa
_virtio=	virtio
_x86bios=	x86bios
.elif ${MACHINE} == "pc98"
_canbepm=	canbepm
_canbus=	canbus
_pmc=		pmc
_snc=		snc
.endif
.endif

.if ${MACHINE_CPUARCH} == "amd64"
_aac=		aac
_aacraid=	aacraid
_aout=		aout
_acpi=		acpi
.if ${MK_CRYPT} != "no" || defined(ALL_MODULES)
_aesni=		aesni
.endif
_agp=		agp
_an=		an
_amdsbwd=	amdsbwd
_amdtemp=	amdtemp
_arcmsr=	arcmsr
_asmc=		asmc
_bxe=		bxe
_cardbus=	cardbus
_cbb=		cbb
_cmx=		cmx
_ciss=		ciss
_coretemp=	coretemp
_cpuctl=	cpuctl
_cpufreq=	cpufreq
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_cyclic=	cyclic
.endif
_dpms=		dpms
_drm=		drm
_drm2=		drm2
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_dtrace=	dtrace
.endif
_ed=		ed
_et=		et
_em=		em
_exca=		exca
_ext2fs=	ext2fs
.if ${MK_SOURCELESS_HOST} != "no"
_hpt27xx=	hpt27xx
.endif
_hptiop=	hptiop
.if ${MK_SOURCELESS_HOST} != "no"
_hptmv=		hptmv
_hptnr=		hptnr
_hptrr=		hptrr
.endif
_i2c=		i2c
_ichwd=		ichwd
_ida=		ida
_if_ndis=	if_ndis
_igb=		igb
_iir=		iir
_io=		io
_ipmi=		ipmi
_ips=		ips
_ipw=		ipw
.if ${MK_SOURCELESS_UCODE} != "no"
_ipwfw=		ipwfw
.endif
_isci=		isci
_iwi=		iwi
.if ${MK_SOURCELESS_UCODE} != "no"
_iwifw=		iwifw
.endif
_iwn=		iwn
.if ${MK_SOURCELESS_UCODE} != "no"
_iwnfw=		iwnfw
.endif
_ixgb=		ixgb
_ixgbe=		ixgbe
_lindev=	lindev
_linprocfs=	linprocfs
_linsysfs=	linsysfs
_linux=		linux
_mly=		mly
.if ${MK_OFED} != "no" || defined(ALL_MODULES)
_mlx4=		mlx4
_mlx4ib=	mlx4ib
_mlxen=		mlxen
_mthca=		mthca
.endif
_ndis=		ndis
_nfe=		nfe
_nvd=		nvd
.if ${MK_SOURCELESS_HOST} != "no"
_nve=		nve
.endif
_nvme=		nvme
_nvram=		nvram
_nxge=		nxge
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_opensolaris=	opensolaris
.endif
.if ${MK_CRYPT} != "no" || defined(ALL_MODULES)
_padlock=	padlock
.endif
_pccard=	pccard
_qlxgb=		qlxgb
_rdma=		rdma	
_s3=		s3
_safe=		safe
_scsi_low=	scsi_low
_sfxge=		sfxge
_smbfs=		smbfs
_sound=		sound
_speaker=	speaker
_splash=	splash
_sppp=		sppp
_tpm=		tpm
_twa=		twa
_vesa=		vesa
_viawd=		viawd
_virtio=	virtio
_vxge=  	vxge
_x86bios=	x86bios
_wbwd=		wbwd
_wi=		wi
_wpi=		wpi
.if ${MK_SOURCELESS_UCODE} != "no"
_wpifw=		wpifw
.endif
.if ${MK_ZFS} != "no" || defined(ALL_MODULES)
_zfs=		zfs
.endif
.endif

.if ${MACHINE_CPUARCH} == "ia64"
_aac=		aac
_aacraid=	aacraid
_aic=		aic
_an=		an
_arcnet=	arcnet
_asr=		asr
_bktr=		bktr
_cardbus=	cardbus
_cbb=		cbb
_ciss=		ciss
_cm=		cm
_cmx=		cmx
_coff=		coff
_cpufreq=	cpufreq
_dpt=		dpt
_em=		em
_ep=		ep
_et=		et
_exca=		exca
_fe=		fe
_hptiop=	hptiop
_ida=		ida
_igb=		igb
_iir=		iir
_ips=		ips
_mly=		mly
_pccard=	pccard
_scsi_low=	scsi_low
_smbfs=		smbfs
_sound=		sound
_splash=	splash
_sppp=		sppp
_streams=	streams
_tpm=		tpm
_twa=		twa
_wi=		wi
_xe=		xe
.endif

.if ${MACHINE_CPUARCH} == "powerpc"
_agp=		agp
_an=		an
_bm=		bm
_cpufreq=	cpufreq
_nvram=		powermac_nvram
_smbfs=		smbfs
_sound=		sound
.endif

.if ${MACHINE_ARCH} == "powerpc64"
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_opensolaris=	opensolaris
.endif
.if ${MK_ZFS} != "no" || defined(ALL_MODULES)
_zfs=		zfs
.endif
.endif

.if ${MACHINE_CPUARCH} == "sparc64"
_auxio=		auxio
_em=		em
_epic=		epic
_i2c=		i2c
_igb=		igb
.if ${MK_CDDL} != "no" || defined(ALL_MODULES)
_opensolaris=	opensolaris
.endif
_smbfs=		smbfs
_sound=		sound
.if ${MK_ZFS} != "no" || defined(ALL_MODULES)
_zfs=		zfs
.endif
.endif

.if defined(MODULES_OVERRIDE) && !defined(ALL_MODULES)
SUBDIR=${MODULES_OVERRIDE}
.endif

.for reject in ${WITHOUT_MODULES}
SUBDIR:= ${SUBDIR:N${reject}}
.endfor

# Calling kldxref(8) for each module is expensive.
.if !defined(NO_XREF)
.MAKEFLAGS+=	-DNO_XREF
afterinstall:
	@if type kldxref >/dev/null 2>&1; then \
		${ECHO} kldxref ${DESTDIR}${KMODDIR}; \
		kldxref ${DESTDIR}${KMODDIR}; \
	fi
.endif

.include <bsd.subdir.mk>
