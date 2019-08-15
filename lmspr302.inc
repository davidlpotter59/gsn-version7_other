/* lmspr302.inc

   June 25, 2007 

   SCIPS.com, Inc.

   include file to print mso common forms for LMP policies
*/

deletefile(L_MACRO)

Access SFPMASTER, Set SFPMASTER:POLICY_NO    = G_POLICY_NO,
                      SFPMASTER:POL_YEAR     = G_YEAR,
                      SFPMASTER:END_SEQUENCE = G_END_SEQUENCE, Exact

Access SFPNAME, Set SFPNAME:POLICY_NO    = G_POLICY_NO,
                    SFPNAME:POL_YEAR     = G_YEAR,
                    SFPNAME:END_SEQUENCE = G_END_SEQUENCE, Exact

Access SFSCOMPANY, Set SFSCOMPANY:COMPANY_ID = SFPNAME:COMPANY_ID, Generic

Access SFPLOCATION, Set SFPLOCATION:POLICY_NO    = G_POLICY_NO,
                        SFPLOCATION:POL_YEAR     = G_YEAR,
                        SFPLOCATION:END_SEQUENCE = G_END_SEQUENCE, Generic

Access SFSLINE, Set SFSLINE:COMPANY_ID       = SFPNAME:COMPANY_ID,
                    SFSLINE:LINE_OF_BUSINESS = SFPNAME:LINE_OF_BUSINESS,
                    SFSLINE:LOB_SUBLINE      = "00", Exact

Include "swsut100.inc"  

L_LOB_CODE = SFSLINE:LOB_CODE
Access SCIPSCONTROL, Set SCIPSCONTROL:COMPANY_ID = SFPNAME:COMPANY_ID,
                         SCIPSCONTROL:STATE      = I_STATE,
                         SCIPSCONTROL:LOB_CODE   = L_LOB_CODE, Exact

If SFPPRINT1:NEW_AGENT_NO = "Y" And
   L_COPIES_PRINTED = 1 And 
   SCIPSCONTROL:INSURED_MAILER_PAGE = "" Then
    begin 
    L_REPORT = "sfpmailer"
    Include "sfsmacro1.inc"
    end 
Else  
If L_COPIES_PRINTED = 1 And 
   SCIPSCONTROL:INSURED_MAILER_PAGE <> "" Then
    begin 
    L_REPORT = Trun(SCIPSCONTROL:INSURED_MAILER_PAGE)
    Include "sfsmacro1.inc"
    end 

If SFPMASTER:TRANS_CODE = 12 Or
   SFPMASTER:TRANS_CODE = 13 or
   sfpmaster:trans_code = 15 Then
    Begin
    L_REPORT = "hopsc16"
    Include "sfsmacro1.inc"
    End

Access SCIPSCONTROL, Set SCIPSCONTROL:COMPANY_ID = SFPNAME:COMPANY_ID,
                         SCIPSCONTROL:STATE      = I_STATE,
                         SCIPSCONTROL:LOB_CODE   = L_LOB_CODE, Generic

L_REPORT = SCIPSCONTROL:DEC_PAGE_TO_USE
If SCIPSCONTROL:USE_BATCH_DEC_PAGE = 1 Then
    Begin
    Include "sfsmacro1.inc"
    End
Else
    Begin
    Include "sfsmacro.inc"
    End

Writefile(L_MACRO,"cli rm %s",Trun(L_MACRO))
closefile(L_MACRO)
If SFSCOMPANY:DEBUG_MODE = 0 Then
    Proc("cli cq %s",Trun(L_MACRO))/noconsole
Else
    Proc("cli cq %s",Trun(L_MACRO))
