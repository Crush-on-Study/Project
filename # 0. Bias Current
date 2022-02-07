// Test Function: bias_current
ETS_PRGFLOW_FUNC bias_current( int DSIndex, LPCTSTR TestLabel )
{

    RESULTS_STR hin5[NUM_SITES],lin5[NUM_SITES];
    RESULTS_STR rinh1[NUM_SITES],rinl1[NUM_SITES],rindel[NUM_SITES];

    // Update test numbering information /////////////
    SetTestNumber( TestNmbr[DSIndex] );
    SetSubTestNumber( SubTestNmbr[DSIndex] );
	/////////////////////////////////////////////////

//	cbitclose( K5_GP, K8_GP, K12_GP, K14_GP, K22_GP, K26_GP );
	cbitclose( KS_GP,K1A_S14, K4F_S14, K5A_S14, K6A_S14, K67C_S14, K8D_S14);


	sp100set( VCC_SPU100_GP, SP_FV, 15, SP_30V, SP_1MA );
	sp100set( VB_SPU100_GP, SP_FV, 15, SP_30V, SP_1MA );
	apuset( HIN_APU_GP, APU_FV, 5, APU_10V, APU_100UA, PIN_TO_VI );
	lwait( 5000 ); 
    apumi( HIN_APU_GP, 10, 10 );
	groupgetresults( hin5, NUM_SITES );

 // RINH1 *********************************************************/

	FOR_EACH_SITE( site, NUM_SITES )
	{
		rinh1[site].value = 5 / hin5[site].value;
		msLogResult(site, DSIndex, rinh1[site].value);
	}
	DSIndex=DSIndex+1; IF_FAIL_RETURN;
 
// RINH ***********************************************************/

	msScaleDataAll( 1000, hin5, NUM_SITES );
	msLogResultAll( DSIndex++, hin5, NUM_SITES ); IF_FAIL_RETURN;

 //****************************************************************/

	apuset( HIN_APU_GP, APU_VIOFF, 0, APU_10V, APU_100UA, PIN_TO_VI );
	cbitopen( K1A_S14 );
	cbitclose( K2A_S14 );

	apuset( LIN_APU_GP, APU_FV, 5, APU_10V, APU_1MA, PIN_TO_VI );
	lwait( 1000 );
    apumi( LIN_APU_GP, 10, 10 );
	groupgetresults( lin5, NUM_SITES ); 

 // RINL1 *********************************************************/

	FOR_EACH_SITE( site, NUM_SITES )
	{
		rinl1[site].value = 5 / lin5[site].value;
		msLogResult(site, DSIndex, rinl1[site].value);
	}
	DSIndex=DSIndex+1; IF_FAIL_RETURN;

 // RINL **********************************************************/

	msScaleDataAll( 1000, lin5, NUM_SITES );
	msLogResultAll( DSIndex++, lin5, NUM_SITES ); IF_FAIL_RETURN;

 // RINDEL ********************************************************/

	FOR_EACH_SITE( site, NUM_SITES )
	{
	rindel[site].value = fabs(rinh1[site].value - rinl1[site].value);
	msLogResult( site, DSIndex, rindel[site].value );
	}
	DSIndex=DSIndex+1;  IF_FAIL_RETURN;

 /***********************************************************/

    // Clean Up Code
	sp100set( VCC_SPU100_GP, SP_FV, 0, SP_30V, SP_1MA );
	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_1MA );
	sp100set( VCC_SPU100_GP, SP_OFF, 0, SP_30V, SP_1MA );
	sp100set( VB_SPU100_GP, SP_OFF, 0, SP_30V, SP_1MA );
	apuset( LIN_APU_GP, APU_VIOFF, 0, APU_10V, APU_100UA, PIN_TO_VI );
//	cbitopen( K5_GP, K8_GP, K12_GP, K14_GP, K22_GP, K26_GP );
    cbitopen( K2A_S14, K4F_S14, K5A_S14, K5B_S14, K6A_S14, K67C_S14, K8D_S14, KS_GP );
     
    return( msSiteStat( MS_ALL ) ); // Return w/status
} // END_ETS_PRGFLOW_FUNC
