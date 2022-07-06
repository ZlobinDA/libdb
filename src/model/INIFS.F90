      subroutine igbrec(nar1, idb, lrec, nr)
!
      IMPLICIT NONE
!
      INTEGER*4 MAX_F,L_REC,L_NAM,L_NAMC,L_NOD,MAX_ND,L_NODC,ILARR,IBARR
      INTEGER*4 ICREC,INMEM,NMEM,IDB,NFF,IER,LREC,IN,NR,IFINDN
      INTEGER*4 LRECF,IBFREF,LEVI,NEXTZ,LASTID,IDBM,IREW
!
      character*(*) nar1
      parameter ( max_f = 5, l_rec = 128, l_nam = 4)
      parameter ( l_namc = l_nam*4,l_nod = l_nam + 2,                           &
     &  max_nd = l_rec/l_nod, l_nodc = l_nod*4)
      parameter (ilarr = 6, ibarr = 5)
      character*(l_namc) namew,narr
      character*(l_nodc) buf(max_nd)
      integer*4 nodp(l_nod,max_nd), rec0(l_rec)
      real*4 wnodp((l_nod+1)*max_nd), rec0w(l_rec)
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
      equivalence (buf(1),nodp(1,1),wnodp(1)),                                  &
     & (rec0(1),rec0w(1))
!********************************************************************
      narr = nar1
      call toupper(narr, namew)
      icrec = 2
      inmem = nmem(idb)
 4    call rdrec(nff(idb), icrec, l_rec, wnodp,ier)
      if(ier.lt.0) then
        lrec = -10
        return
      end if
      in = ifindn(namew, buf, inmem)
      if(in.eq.0) goto 3
      nr = nodp(ilarr,in)
      lrec = nodp(ibarr,in)
      if(nr.lt.0) then
        icrec = lrec
        inmem = abs(nr)
        goto 4
      end if
      if(namew.ne.buf(in)(1:l_namc)) goto 3
      return
 3    lrec = -2
      return
      end
!!!
      subroutine inifs
!
      IMPLICIT NONE
!
      INTEGER*4 MAX_F,L_REC,L_NAM,L_NAMC,L_NOD,MAX_ND,L_NODC,ILARR,IBARR
      INTEGER*4 NFF,LRECF,IBFREF,LEVI,NMEM,NEXTZ,LASTID,IDBM,INMEM,IREW
      INTEGER*4 I,IDB,NF,IER,IRR,IDB1,IDB2
!
      parameter ( max_f = 5, l_rec = 128, l_nam = 4)
      parameter (                                                               &
     & l_namc = l_nam*4,l_nod = l_nam + 2, max_nd = l_rec/l_nod,                &
     & l_nodc = l_nod*4)
      character*(*) namf
      logical exis
      parameter (ilarr = 6, ibarr = 5)
      character*(l_nodc) buf(max_nd)
      integer*4 nodp(l_nod,max_nd), rec0(l_rec)
      real*4 wnodp((l_nod+1)*max_nd), rec0w(l_rec)
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
      equivalence (buf(1),nodp(1,1),wnodp(1)),                                  &
     & (rec0(1),rec0w(1))
!********************************************************************
      idbm = 0
      irew = 0
      do 1 i = 1, max_f
        lrecf(i) = l_rec
        lastid(i) = 0
        nextz(i) = 0
        nff(i) = 0
 1      levi(i) = 2
      return
!
      entry opefs(namf, nf, idb)
      call getfidb(idb)
      if(idb.lt.0) then
        idb = -1
        return
      end if
      nff(idb) = nf
      open(nf, file=namf, recl=lrecf(idb)*4, access='direct',                   &
     & share='denynone')
      call rdrec(nff(idb), 1, lrecf(idb), rec0w, ier)
      if(ier.lt.0) then
        close(nff(idb))
        idb = -20
        return
      end if
      if(rec0(1).ne.1967750) then
        close(nff(idb))
        nff(idb) = 0
        idbm = idbm - 1
        idb = -20
        return
      end if
      ibfref(idb)=rec0(2)
      nmem(idb)=rec0(3)
      return
!
      entry crefs(namf, nf, idb)
      call getfidb(idb)
      if(idb.lt.0) then
        idb = -1
        return
      end if
      nff(idb) = nf
      ibfref(idb) = 3
      nmem(idb) = 1
      inquire(file=namf,exist=exis)
      if(exis) then
        open(nf, file=namf, recl=lrecf(idb)*4, access='direct')
        close(nf,status='delete')
      end if
      open(nf, file=namf, recl=lrecf(idb)*4, access='direct',                   &
     & share='denynone')
      do 2 i = 1, max_nd
        buf(i)(1:l_namc) = ' '
        nodp(ilarr,i) = 0
        nodp(ibarr,i) = 0
 2    continue
      buf(1)(1:l_namc)='~~~~~~~~~~~~~~~0'
      nodp(ilarr,1)=l_nod
      nodp(ibarr,1)=2
      call wrrec(nff(idb), 2, lrecf(idb), wnodp)
      do 44 i = 1, lrecf(idb)
  44   rec0(i) = 0
      rec0(1)=1967750
      rec0(2)=ibfref(idb)
      rec0(3)=nmem(idb)
      irr=1
      call wrrec(nff(idb), irr, lrecf(idb), rec0w)
      return
!
      entry wrrec0(idb1)
      do 4 i = 1, lrecf(idb1)
  4   rec0(i) = 0
      rec0(1)=1967750
      rec0(2)=ibfref(idb1)
      rec0(3)=nmem(idb1)
      irr=1
      call wrrec(nff(idb1), irr, lrecf(idb1), rec0w)
      return
!
      entry closfs(idb2)
      if(idbm.eq.0) return
      if(idb2.gt.max_f) return
      close(nff(idb2))
      nff(idb2) = 0
      idbm = idbm - 1
      return
      end
!!!
      subroutine addcat(idb, nar1, ir, n, ier)
!
      IMPLICIT NONE
!
      INTEGER*4 MAX_F,L_REC,L_NAM,L_NAMC,L_NOD,MAX_ND,L_NODC,ILARR,IBARR
      INTEGER*4 NFF,LRECF,IBFREF,LEVI,NMEM,NEXTZ,LASTID,IDBM,INMEM,IREW
      INTEGER*4 I,IREZZ,IER,IDB,I1,N,ICREC,IPCREC,INP,IN,IFINDN,LREC,NR
      INTEGER*4 IR,I12
!
      parameter ( max_f = 5, l_rec = 128, l_nam = 4)
      parameter (l_namc = l_nam*4,l_nod = l_nam + 2,                            &
     & max_nd = l_rec/l_nod,                                                    &
     & l_nodc = l_nod*4)
      character*(*) nar1
      parameter (ilarr = 6, ibarr = 5)
      character*(l_namc) narr, namew
      character*(l_nodc) buf(max_nd)
      integer*4 nodp(l_nod,max_nd), rec0(l_rec)
      real*4 wnodp((l_nod+1)*max_nd), rec0w(l_rec)
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
      equivalence (buf(1),nodp(1,1),wnodp(1)),                                  &
     & (rec0(1),rec0w(1))
!********************************************************************
      irezz = ier
      ier = 0
      narr = nar1
      if(narr.eq.' ') then
        if(lastid(idb).eq.0) then
          ier = -10
          return
        end if
        i1 = lastid(idb)
        call rdrec(nff(idb), levi(idb), l_rec, wnodp,ier)
        if(ier.lt.0) then
          ier = -10
          return
        end if
        nodp(ilarr,i1) = nodp(ilarr,i1) + n
        call wrrec(nff(idb), levi(idb), l_rec, wnodp)
        call wrrec0(idb)
        return
      end if
      call toupper(narr, namew)
      icrec = 2
      ipcrec = 0
      inmem = nmem(idb)
 4    call rdrec(nff(idb), icrec, l_rec, wnodp,ier)
      if(ier.lt.0) then
        ier = -10
        return
      end if
      inp = in
      in = ifindn(namew, buf, inmem)
      if(in.eq.0) then
        ier = -10
        return
      end if
      lrec = nodp(ilarr,in)
      nr = nodp(ibarr,in)
      narr = buf(in)(1:l_namc)
      if(lrec.lt.0) then
        ipcrec = icrec
        icrec = nr
        inmem = abs(lrec)
        goto 4
      end if
      if(namew.eq.buf(in)(1:l_namc)) then
        ier = -10
        return
      end if
      if(inmem.lt.max_nd) then
        do 2 i = inmem, in, -1
          buf(i+1) = buf(i)
 2      continue
        buf(in)(1:l_namc) = namew
        nodp(ibarr,in) = ir
        nodp(ilarr,in) = n
        call wrrec(nff(idb), icrec, l_rec, wnodp)
        if(ipcrec.ne.0) then
          call rdrec(nff(idb), ipcrec, l_rec, wnodp,ier)
          if(ier.lt.0) then
            ier = -10
            return
          end if
          nodp(ilarr,inp) = -(inmem + 1)
          call wrrec(nff(idb), ipcrec, l_rec, wnodp)
        else
          nmem(idb) = nmem(idb) + 1
        end if
      else
        nodp(ibarr,in) = irezz
        nodp(ilarr,in) = -2
        call wrrec(nff(idb), icrec, l_rec, wnodp)
        in = 1
        do 12 i12 = 1, max_nd
          buf(i12)(1:l_namc) = ' '
          nodp(ilarr,i12) = 0
          nodp(ibarr,i12) = 0
 12     continue
        icrec = irezz
        buf(in)(1:l_namc) = namew
        nodp(ibarr,in) = ir
        nodp(ilarr,in) = n
        buf(in+1)(1:l_namc) = narr
        nodp(ibarr,in+1) = nr
        nodp(ilarr,in+1) = lrec
        call wrrec(nff(idb), icrec, l_rec, wnodp)
      end if
      do 6 i = 1, max_f
 6      lastid(i) = 0
      lastid(idb) = in
      levi(idb) = icrec
      call wrrec0(idb)
      return
      end
!!!
      subroutine wrarr(nar1, idb, a, n, ier)
!
      IMPLICIT NONE
!
      INTEGER*4 MAX_F,L_NAM,L_REC,L_NAMC,L_NOD,MAX_ND,IDB,IER,NF,LREC
      INTEGER*4 NFF,LRECF,IBFREF,LEVI,NMEM,NEXTZ,LASTID,IDBM,INMEM,IREW
      INTEGER*4 IBFREC,IBFREO,IR0,NR0,IREZZ,NRF,NO,IBEGO,MOD,IB,I,N
!
      parameter ( max_f = 5, l_nam = 4,l_rec = 128)
      parameter (l_namc = l_nam*4,l_nod = l_nam + 2,                            &
     & max_nd = l_rec/l_nod)
      character*(*) nar1
      character*(l_namc) narr
      real*4 a(n)
      LOGICAL LREW
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
!********************************************************************
      if(idb.gt.max_f.or.idb.le.0) then
        ier = -11
        return
      end if
      narr = nar1
      nf = nff(idb)
      lrec = lrecf(idb)
      if(narr.eq.' ') then
        if(NEXTZ(IDB).LE.0) then
          ier = -1
          return
        end if
        ibfrec = nextz(idb)
      else
        ibfrec = ibfref(idb)
        ibfreo = ibfrec
        irew=0
        call igbrec(narr, idb, ir0, nr0)
        if(ir0.gt.0) then
          irew = NR0
          ibfrec = ir0
        end if
        if(ir0.eq.-10) then
          ier = -10
          return
        end if
      end if
      if(inmem.eq.max_nd.and.narr.ne.' '.and.irew.EQ.0) then
       irezz = ibfrec
       ibfrec = ibfrec + 1
       ibfreo = ibfrec
      end if
      LREW = IREW.GT.0
      nrf = n / lrec
      IF(LREW) THEN
        IREW = IREW - N
        IF(IREW.LT.0) THEN
          IER = -1
          RETURN
        END IF
      END IF
      if(nrf.eq.0) then
        no = n
        ibego = 1
      else
        no = mod(n, lrec)
        ibego = nrf * lrec + 1
      end if
      ib = 1
      do 1 i=1,nrf
        call wrrec(nf, ibfrec, lrec, a(ib))
        ib = ib + lrec
        ibfrec = ibfrec + 1
 1    continue
      if(no.gt.0) then
        call wrrec(nf, ibfrec, no, a(ibego))
        ibfrec = ibfrec + 1
      end if
      nextz(idb)=ibfrec
      if(LREW) return
      ibfref(idb) = ibfrec
      ier = irezz
      call addcat(idb, narr, ibfreo, n, ier)
      return
      end
!!!
      subroutine rdarr(nar1, idb, a, n, ier)
!
      IMPLICIT NONE
!
      INTEGER*4 MAX_F,L_NAM,L_NAMC,N,NR,IER,IDB,NF,LREC,IBFREC,N1,NRF
      INTEGER*4 NFF,LRECF,IBFREF,LEVI,NMEM,NEXTZ,LASTID,IDBM,INMEM,IREW
      INTEGER*4 NO,IBEGO,MOD,IB,I
!
      parameter ( max_f = 5, l_nam = 4)
      parameter ( l_namc = l_nam*4)
      character*(*) nar1
      character*(l_namc) narr
      real*4 a(n)
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
!********************************************************************
      NR=90000000
      ier = 0
      if(idb.gt.max_f.or.idb.le.0) then
        ier = -11
        return
      end if
      narr = nar1
      nf = nff(idb)
      lrec = lrecf(idb)
      if(narr.ne.' ') then
        call igbrec(narr, idb, ibfrec, nr)
        if(ibfrec.le.0) then
          ier = ibfrec
          return
        end if
      else
        if(nextz(idb).eq.0) then
          ier = -10
          return
        end if
        ibfrec = nextz(idb)
      end if
      n1 = min(nr, n)
      nrf = n1 / lrec
      if(nrf.eq.0) then
        no = n1
        ibego = 1
      else
        no = mod(n1, lrec)
        ibego = nrf * lrec + 1
      end if
      ib = 1
      do 1 i=1,nrf
        call rdrec(nf, ibfrec, lrec, a(ib),ier)
        if(ier.lt.0) then
          ier = -10
          return
        end if
        ib = ib + lrec
        ibfrec = ibfrec + 1
 1    continue
      if(no.gt.0) then
        call rdrec(nf, ibfrec, no, a(ibego),ier)
        if(ier.lt.0) then
          ier = -10
          return
        end if
        ibfrec = ibfrec + 1
      end if
      ier = n1
      nextz(idb)=ibfrec
      return
      end
!!!
      subroutine getfidb(idb)
!
      IMPLICIT NONE
!
      INTEGER*4 NFF,LRECF,IBFREF,LEVI,NMEM,NEXTZ,LASTID,IDBM,INMEM,IREW
      INTEGER*4 MAX_F,IDB,I
!
      parameter ( max_f = 5)
      common/filsys/nff(max_f),lrecf(max_f),ibfref(max_f),levi(max_f),          &
     & nmem(max_f),nextz(max_f),lastid(max_f),idbm,inmem,irew
!********************************************************************
      if (idbm.lt.max_f) then
        do 1 i=1, max_f
          if(nff(i).eq.0) then
            idb = i
            idbm = idbm + 1
            return
          end if
 1      continue
      end if
      idb = -1
      return
      end
!!!
      subroutine wrrec(nf, ir, n, a)
!
      IMPLICIT NONE
!
      INTEGER*4 N,IR,NF
      real*4 a(n)
!
      write (nf, rec=ir) a
      return
      end
!!!
      subroutine rdrec(nf, ir, n, a, ier)
!
      IMPLICIT NONE
!
      INTEGER*4 N,IER,NF,IR
      real*4 a(n)
! 
      ier = 0
      read (nf, rec=ir,err=100) a
      return
100   ier = -1
      return
      end
!!!
      subroutine toupper(nami, namo)
!
      IMPLICIT NONE
!
      INTEGER*4 IC1,L,I
      character*(*) nami, namo
!********************************************************************
      l = len(namo)
      do 1 i = 1, l
        ic1 = ichar(nami(i:i))
        if (ic1.ge.97.and.ic1.le.122) ic1 = ic1 - 32
        namo(i:i) = char(ic1)
 1    continue
      return
      end
!!!
      function ifindn(nam1, aname, n)
!
      IMPLICIT NONE
!
      INTEGER*4 L_NAM,L_NAMC,L_NOD,L_NODC,IFINDN,I1,I,N
!
      parameter ( l_nam = 4)
      parameter (                                                               &
     & l_namc = l_nam*4,l_nod = l_nam + 2, l_nodc = l_nod*4)
      character*(*) nam1
      character name*(l_namc)
      character*(l_nodc) aname(n)
!********************************************************************
      name = nam1
      i1 = 0
      do 1 i = 1, n
        if (name.le.aname(i)(1:l_namc)) then
          i1 = i
          go to 2
        end if
 1    continue
 2    ifindn = i1
      return
      end
