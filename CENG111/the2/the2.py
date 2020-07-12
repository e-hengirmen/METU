def isCovered(cp_bl, cp_tr, t1_bl, t1_tr, t2_bl, t2_tr):
    t1_bl0=min(max(t1_bl[0],cp_bl[0]),cp_tr[0])
    t1_bl1=min(max(t1_bl[1],cp_bl[1]),cp_tr[1])

    t1_tr0=min(max(t1_tr[0],cp_bl[0]),cp_tr[0])
    t1_tr1=min(max(t1_tr[1],cp_bl[1]),cp_tr[1])

    t2_bl0=min(max(t2_bl[0],cp_bl[0]),cp_tr[0])
    t2_bl1=min(max(t2_bl[1],cp_bl[1]),cp_tr[1])

    t2_tr0=min(max(t2_tr[0],cp_bl[0]),cp_tr[0])
    t2_tr1=min(max(t2_tr[1],cp_bl[1]),cp_tr[1])

    cpX=cp_tr[0]-cp_bl[0]
    cpY=cp_tr[1]-cp_bl[1]

    t1X=t1_tr0-t1_bl0
    t1Y=t1_tr1-t1_bl1

    t2X=t2_tr0-t2_bl0
    t2Y=t2_tr1-t2_bl1


    kesisimX=min(t1_tr0,t2_tr0)-max(t1_bl0,t2_bl0)
    if kesisimX<0:
        kesisimX=0
    kesisimY=min(t1_tr1,t2_tr1)-max(t1_bl1,t2_bl1)
    if kesisimY<0:
        kesisimY=0


    sonuc=t1X*t1Y+t2X*t2Y-kesisimX*kesisimY
    
    if sonuc==cpX*cpY:
        return "COMPLETELY COVERED"
    else:
        return "NOT COMPLETELY COVERED"