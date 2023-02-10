// Test Function: Zener
ETS_PRGFLOW_FUNC Zener( int DSIndex, LPCTSTR TestLabel )
{
    RESULTS_STR isetl[NUM_SITES], iseth[NUM_SITES], set_r[NUM_SITES];
	RESULTS_STR iresetl[NUM_SITES], ireseth[NUM_SITES], reset_r[NUM_SITES];
	RESULTS_STR delset[NUM_SITES];
	RESULTS_STR setbv1[NUM_SITES], setbv2[NUM_SITES], delbv1[NUM_SITES];
	RESULTS_STR resetbv1[NUM_SITES], resetbv2[NUM_SITES], delbv2[NUM_SITES];
	
    // Update test numbering information
    SetTestNumber( TestNmbr[DSIndex] );
    SetSubTestNumber( SubTestNmbr[DSIndex] );

	//=========== SET_RESISTANCE ======
	cbitopen( K1A_S14,K1B_S14,K2A_S14,K2B_S14,K4A_S14,K4B_S14,K4C_S14,K4D_S14,K4E_S14,K4F_S14,K4G_S14, KH_S14);
	cbitopen( K5A_S14,K5B_S14,K5C_S14,K5D_S14,K6A_S14,K6E_S14, K6F_S14,KH_S14,K67A_S14,K67B_S14,K67C_S14);
	cbitopen( K7A_S14,K7B_S14,K7C_S14,K78B_S14,K78A_S14,K8A_S14,K8B_S14,K8C_S14,K8D_S14,K8E_S14,KSET_S14,KRESET_S14);
	lwait( 1000 );
	cbitclose( KS_GP, K8D_S14, KSET_S14);
	lwait( 3000 );

	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	lwait( 1000 );

	sp100set( VB_SPU100_GP, SP_FV, 3.0, SP_30V, SP_10MA );

	lwait( 10000 );	
    sp100mi( VB_SPU100_GP, SP_MV_1X, SP_MI_1X , 10, 10 );
	groupgetresults( isetl, NUM_SITES );
	msScaleDataAll( 1000, isetl, NUM_SITES );
	msLogResultAll( DSIndex++, isetl, NUM_SITES );	//IF_FAIL_RETURN;

	sp100set( VB_SPU100_GP, SP_FV, 7.0, SP_30V, SP_10MA );
	lwait( 1000 );						
    sp100set( VB_SPU100_GP, SP_FV, 6.5, SP_30V, SP_10MA );
	lwait( 5000 );						
	sp100mi( VB_SPU100_GP, SP_MV_1X, SP_MI_1X , 10, 10 );
	groupgetresults( iseth, NUM_SITES );
	msScaleDataAll( 1000, iseth, NUM_SITES );
	msLogResultAll( DSIndex++, iseth, NUM_SITES );	//IF_FAIL_RETURN;

  
	FOR_EACH_SITE( site, NUM_SITES )
	{
		set_r[site].value = 3.5 / fabs(isetl[site].value - iseth[site].value)*1000;
		msLogResult(site, DSIndex, set_r[site].value);
	}


	DSIndex=DSIndex+1;  IF_FAIL_RETURN;


	//=========== RESET_RESISTANCE ======
	cbitopen( KSET_S14);

	cbitclose( KRESET_S14 );
	lwait( 3000 );

	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	lwait( 1000 );

	sp100set( VB_SPU100_GP, SP_FV, 3.0, SP_30V, SP_10MA );
	lwait( 10000 );						
    sp100mi( VB_SPU100_GP, SP_MV_1X, SP_MI_1X , 10, 10 );
	groupgetresults( iresetl, NUM_SITES );
	msScaleDataAll( 1000, iresetl, NUM_SITES );
	msLogResultAll( DSIndex++, iresetl, NUM_SITES );	//IF_FAIL_RETURN;

	sp100set( VB_SPU100_GP, SP_FV, 7.0, SP_30V, SP_10MA );
	lwait( 1000 );	
	sp100set( VB_SPU100_GP, SP_FV, 6.5, SP_30V, SP_10MA );
	lwait( 5000 );						
    sp100mi( VB_SPU100_GP, SP_MV_1X, SP_MI_1X , 10, 10 );
	groupgetresults( ireseth, NUM_SITES );
	msScaleDataAll( 1000, ireseth, NUM_SITES );
	msLogResultAll( DSIndex++, ireseth, NUM_SITES );	//IF_FAIL_RETURN;


	FOR_EACH_SITE( site, NUM_SITES )
	{
		reset_r[site].value = 3.5 / fabs(iresetl[site].value - ireseth[site].value)*1000;
		msLogResult(site, DSIndex, reset_r[site].value);
	}
	DSIndex=DSIndex+1;  IF_FAIL_RETURN;


	//////////////////DELSET///////////////////////////
	FOR_EACH_SITE( site, NUM_SITES )
	{
		delset[site].value = fabs(set_r[site].value - reset_r[site].value);
		msLogResult( site, DSIndex, delset[site].value );
	}
	DSIndex=DSIndex+1;  IF_FAIL_RETURN;

	//=========== SET_BV ======
	
	cbitopen( KRESET_S14);

	cbitclose( KSET_S14 );
	lwait( 3000 );

	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	lwait( 1000 );
	sp100set( VB_SPU100_GP, SP_FI, 2.0, SP_30V, SP_10MA );
	lwait( 10000 );	

    sp100mv( VB_SPU100_GP, SP_MV_1X, SP_MI_1X, 200, 10 );
	groupgetresults( setbv1, NUM_SITES );
//	msScaleDataAll( 1000,setbv1, NUM_SITES );
	msLogResultAll( DSIndex++, setbv1, NUM_SITES );	//IF_FAIL_RETURN;

	sp100set( VB_SPU100_GP, SP_FI, 1.5, SP_30V, SP_10MA );
	lwait( 10000 );	

    sp100mv( VB_SPU100_GP, SP_MV_1X, SP_MI_1X, 200, 10 );
	groupgetresults( setbv2, NUM_SITES );
//	msScaleDataAll( 1000,setbv2, NUM_SITES );
	msLogResultAll( DSIndex++, setbv2, NUM_SITES );	//IF_FAIL_RETURN;

  //=========== RESET_BV ======
	
	cbitopen( KSET_S14);

	cbitclose( KRESET_S14 );
	lwait( 3000 );

	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	lwait( 1000 );
	sp100set( VB_SPU100_GP, SP_FI, 2.0, SP_30V, SP_10MA );
	lwait( 10000 );	

    sp100mv( VB_SPU100_GP, SP_MV_1X, SP_MI_1X, 200, 10 );
	groupgetresults( resetbv1, NUM_SITES );
//	msScaleDataAll( 1000,resetbv1, NUM_SITES );
	msLogResultAll( DSIndex++, resetbv1, NUM_SITES );	//IF_FAIL_RETURN;

	sp100set( VB_SPU100_GP, SP_FI, 1.5, SP_30V, SP_10MA );
	lwait( 10000 );	

    sp100mv( VB_SPU100_GP, SP_MV_1X, SP_MI_1X, 200, 10 );
	groupgetresults( resetbv2, NUM_SITES );
//	msScaleDataAll( 1000,resetbv2, NUM_SITES );
	msLogResultAll( DSIndex++, resetbv2, NUM_SITES );	//IF_FAIL_RETURN;

	FOR_EACH_SITE( site, NUM_SITES )
	{
		delbv1[site].value = setbv1[site].value - resetbv1[site].value;
		msLogResult(site, DSIndex, delbv1[site].value);
	}


	DSIndex=DSIndex+1;  IF_FAIL_RETURN;

	FOR_EACH_SITE( site, NUM_SITES )
	{
		delbv2[site].value = setbv2[site].value - resetbv2[site].value;
		msLogResult(site, DSIndex, delbv2[site].value);
	}


	DSIndex=DSIndex+1;  IF_FAIL_RETURN;

	// Clean Up Code
	sp100set( VCC_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_10MA );
	sp100set( VCC_SPU100_GP, SP_OFF, 0, SP_30V, SP_10MA );
	sp100set( VB_SPU100_GP, SP_OFF, 0, SP_30V, SP_10MA );
	cbitopen( K1A_S14,K1B_S14,K2A_S14,K2B_S14,K4A_S14,K4B_S14,K4C_S14,K4D_S14,K4E_S14,K4F_S14,K4G_S14, KH_S14);
	cbitopen( K5A_S14,K5B_S14,K5C_S14,K5D_S14,K6A_S14,K6E_S14, K6F_S14,KH_S14,K67A_S14,K67B_S14,K67C_S14);
	cbitopen( K7A_S14,K7B_S14,K7C_S14,K78B_S14,K78A_S14,K8A_S14,K8B_S14,K8C_S14,K8D_S14,K8E_S14,KSET_S14,KRESET_S14);
     
    return( msSiteStat( MS_ALL ) ); // Return w/status
} // END_ETS_PRGFLOW_FUNC
