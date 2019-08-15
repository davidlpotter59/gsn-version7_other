/* imspr301.inc
   january 9, 2003

   SCIPS.com, Inc.

   include file to print mso dec page and forms
*/

Deletefile(L_MACRO)

Access SFPMASTER, Set SFPMASTER:POLICY_NO = G_POLICY_NO,
                      SFPMASTER:POL_YEAR = G_YEAR,
                      SFPMASTER:END_SEQUENCE = G_END_SEQUENCE, Exact

Access SFPNAME, Set SFPNAME:POLICY_NO = G_POLICY_NO,
                    SFPNAME:POL_YEAR = G_YEAR,
                    SFPNAME:END_SEQUENCE = G_END_SEQUENCE, Exact

Access SFSCOMPANY, Set SFSCOMPANY:COMPANY_ID = SFPNAME:COMPANY_ID, Generic

/*add this code for a company that has to mail all the policies to the insured
  and to all the mortgagees on a policy
*/
Access SFPLOCATION, Set SFPLOCATION:POLICY_NO    = G_POLICY_NO,
                        SFPLOCATION:POL_YEAR     = G_YEAR,
                        SFPLOCATION:END_SEQUENCE = G_END_SEQUENCE, Generic

Access SFSLINE, Set SFSLINE:COMPANY_ID       = SFPNAME:COMPANY_ID,
                    SFSLINE:LINE_OF_BUSINESS = SFPNAME:LINE_OF_BUSINESS,
                    SFSLINE:LOB_SUBLINE      = "00", Exact

Include "swsut100.inc"  --converts the str_state to a 2 digit number uses sfplocation

L_LOB_CODE = SFSLINE:LOB_CODE
Access SCIPSCONTROL, Set SCIPSCONTROL:COMPANY_ID = SFPNAME:COMPANY_ID,
                         SCIPSCONTROL:STATE      = I_STATE,
                         SCIPSCONTROL:LOB_CODE   = L_LOB_CODE, Exact

If ((SFPPRINT1:NEW_AGENT_NO = "Y") And
   (L_COPIES_PRINTED = 1)) And (Trun(SCIPSCONTROL:INSURED_MAILER_PAGE) = "") Then
    {
    L_REPORT = "sfpmailer"
    Include "sfsmacro1.inc"
    }
Else  
    If (L_COPIES_PRINTED = 1) And (SCIPSCONTROL:INSURED_MAILER_PAGE <> "") Then
        {
        L_REPORT = Trun(SCIPSCONTROL:INSURED_MAILER_PAGE)
        Include "sfsmacro1.inc"
        }

-- wh16 endorsement changes

If SFPMASTER:TRANS_CODE = 12 Or
   SFPMASTER:TRANS_CODE = 13 Then
      Begin
      L_REPORT = "hopsc16"
      Include "sfsmacro1.inc"
      End

-- dec page

Access SCIPSCONTROL, Set SCIPSCONTROL:COMPANY_ID = SFPNAME:COMPANY_ID,
                         SCIPSCONTROL:STATE = I_STATE,
                         SCIPSCONTROL:LOB_CODE = L_LOB_CODE, Generic

L_REPORT = SCIPSCONTROL:DeC_PAGE_TO_USE -- common
If SCIPSCONTROL:USE_BATCH_DEC_PAGE = 1 Then
      Begin
      Include "sfsmacro1.inc"
      End
Else
      Begin
      Include "sfsmacro.inc"
      End

If SFPMASTER:TRANS_CODE = 10 and
   sfpmaster:terrorism_premium <> 0 and
   scipscontrol:dont_print_tpd4_new_business one of 0 Then
    Begin
    L_REPORT = "tpd4"
    Include "sfsmacro1.inc"
    End

If SFPMASTER:TRANS_CODE = 14 and
   sfpmaster:terrorism_premium <> 0 Then
    Begin
    L_REPORT = "tpd5"
    Include "sfsmacro1.inc"
    End

If SFSCOMPANY:PRINT_ENDORSEMENTS = "Y" Then
    Begin
    Access SFPEND, Set SFPEND:POLICY_NO = G_POLICY_NO,
                       SFPEND:POL_YEAR = G_YEAR,
                       SFPEND:END_SEQUENCE = G_END_SEQUENCE, Approximate

    Repeat Begin
        Exit If SFPEND:POLICY_NO <> G_POLICY_NO Or
                SFPEND:POL_YEAR <> G_YEAR Or
                SFPEND:END_SEQUENCE <> G_END_SEQUENCE

        if sfpend:ok_print = "Y" or
           imsdefault:Dont_print_opt_end = 0 then 
            begin
            L_PARAMETER = "scsmca301.par"
            L_CODE = SFPEND:CODE/raw
            L_PREMIUM = SFPEND:PREMIUM
            Do ACCESS_SFSOPTEND
            Do ENDORSEMENT_PRINT
            end

    Next SFPEND
    End

    End

Writefile(L_MACRO,"cli rm %s",Trun(L_MACRO))
Closefile(L_MACRO)
If SFSCOMPANY:DEBUG_MODE = 0 Then
    Proc("cli cq %s",Trun(L_MACRO))/noconsole
Else
    Proc("cli cq %s",Trun(L_MACRO))
