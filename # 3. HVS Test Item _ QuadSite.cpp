// Test Function: HVS_P // [Rev 1.0 : Add for HVS VB-HO-VS connection check on 06/FEB/2017]
ETS_PRGFLOW_FUNC HVS_P( int DSIndex, LPCTSTR TestLabel )
{
 
 //	int site,i;

	double bv10_s1, bv10_s2, bv10_s3, bv10_s4;

    // Update test numbering information ////////////
    SetTestNumber( TestNmbr[DSIndex] );
    SetSubTestNumber( SubTestNmbr[DSIndex] );
    ////////////////////////////////////////////////

    sp100set( VB_SPU100_S1, SP_VMETER, 0.0, SP_1KV, SP_10MA );
    sp100set( VB_SPU100_S2, SP_VMETER, 0.0, SP_1KV, SP_10MA );
    sp100set( VB_SPU100_S3, SP_VMETER, 0.0, SP_1KV, SP_10MA );
    sp100set( VB_SPU100_S4, SP_VMETER, 0.0, SP_1KV, SP_10MA );

	FOR_EACH_SITE( site, NUM_SITES )
	{
		switch(site)
		{

//************************************************************************************************					
// Site1
//************************************************************************************************
			case 0:
				lwait(1000); 

					cbitclose(KS_S1, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 1000 );

					sp500set( VS_SPU500L_S12, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					sp500set( VS_SPU500L_S12, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);
	
					bv10_s1= sp100mv( VB_SPU100_S1, SP_MV_1X, SP_MI_1X, 10, 10 );
					msLogResult( site, DSIndex, bv10_s1 );


					sp500set( VS_SPU500L_S12, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					cbitopen(KS_S1, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 5000 );

			break;


//************************************************************************************************					
// Site2
//************************************************************************************************
				case 1:

					cbitclose(KS_S2, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 1000 );

					sp500set( VS_SPU500L_S12, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					sp500set( VS_SPU500L_S12, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );

					lwait( 1000 );	
					bv10_s2= sp100mv( VB_SPU100_S2, SP_MV_1X, SP_MI_1X, 10, 10 );
					msLogResult( site, DSIndex, bv10_s2 );


					sp500set( VS_SPU500L_S12, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S12, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					sp500set( VS_SPU500L_S12, SP_OFF, 0, SP_1MA, SP_NOCLAMP , SP_NOCLAMP );
					sp500set( VS_SPU500U_S12, SP_OFF, 0, SP_1MA, SP_NOCLAMP , SP_NOCLAMP );

					cbitopen(KS_S2, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 5000 );

			break;


//************************************************************************************************					
// Site3
//************************************************************************************************
				case 2:
					cbitclose(KS_S3, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 1000 );

					sp500set( VS_SPU500L_S34, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					sp500set( VS_SPU500L_S34, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					bv10_s3= sp100mv( VB_SPU100_S3, SP_MV_1X, SP_MI_1X, 10, 10 );
					msLogResult( site, DSIndex, bv10_s3 );


					sp500set( VS_SPU500L_S34, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(5000);

					cbitopen(KS_S3, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 5000 );
			break;

//************************************************************************************************					
// Site4
//************************************************************************************************
				case 3:
					cbitclose(KS_S4, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 1000 );

					sp500set( VS_SPU500L_S34, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 0, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					sp500set( VS_SPU500L_S34, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 5, SP_10MA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);

					bv10_s4= sp100mv( VB_SPU100_S4, SP_MV_1X, SP_MI_1X, 10, 10 );
					msLogResult( site, DSIndex, bv10_s4 );


					sp500set( VS_SPU500L_S34, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait( 1000 );
					sp500set( VS_SPU500U_S34, SP_FV, 0, SP_100UA, SP_NOCLAMP , SP_NOCLAMP );
					lwait(1000);
					sp500set( VS_SPU500L_S34, SP_OFF, 0, SP_1MA, SP_NOCLAMP , SP_NOCLAMP );
					sp500set( VS_SPU500U_S34, SP_OFF, 0, SP_1MA, SP_NOCLAMP , SP_NOCLAMP );

					cbitopen(KS_S4, K67A_S14, K78A_S14, K8E_S14, K6E_S14);
					lwait( 5000 );

			break;
		}
	}

	// Clean Up Code

sp100set( VB_SPU100_S1, SP_OFF, 0, SP_30V, SP_10MA );
sp100set( VB_SPU100_S2, SP_OFF, 0, SP_30V, SP_10MA );
sp100set( VB_SPU100_S3, SP_OFF, 0, SP_30V, SP_10MA );
sp100set( VB_SPU100_S4, SP_OFF, 0, SP_30V, SP_10MA );

cbitopen(KS_S1, KS_S2, KS_S3, KS_S4, K67A_S14, K78A_S14, K8E_S14, K6E_S14);	

    return( msSiteStat( MS_ALL ) ); // Return w/status
} // END_ETS_PRGFLOW_FUNC
