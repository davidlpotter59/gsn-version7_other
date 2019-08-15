/* bpspr302.inc

   november 22, 2000

   SCIPS.com, Inc.

   include file to print mso dec page and forms
*/

deletefile(L_MACRO)

Access SFPMASTER, Set SFPMASTER:POLICY_NO = G_POLICY_NO,
                      SFPMASTER:POL_YEAR = G_YEAR,
                      SFPMASTER:END_SEQUENCE = G_END_SEQUENCE, Exact

Access SFPMASTSUPP, Set SFPMASTSUPP:POLICY_NO = G_POLICY_NO,
                        SFPMASTSUPP:POL_YEAR = G_YEAR,
                        SFPMASTSUPP:END_SEQUENCE = G_END_SEQUENCE, 
                        sfpmastsupp:line_of_business = l_lob, Exact

access bopgeneral, set bopgeneral:policy_no = g_policy_no,
                       bopgeneral:pol_year = g_year,
                       bopgeneral:end_sequence = g_end_sequence, generic

Access SFPNAME, Set SFPNAME:POLICY_NO = G_POLICY_NO,
                    SFPNAME:POL_YEAR = G_YEAR,
                    SFPNAME:END_SEQUENCE = G_END_SEQUENCE, Exact

l_line_of_business = bopgeneral:line_of_business
if l_line_of_business = 0 then
    l_line_of_business = sfpname:line_of_business
Access SFSCOMPANY, Set SFSCOMPANY:COMPANY_ID = SFPNAME:COMPANY_ID, Generic

/*add this code for a company that has to mail all the policies to the insured
  and to all the mortgagees on a policy
*/
Access SFPLOCATION, Set SFPLOCATION:POLICY_NO    = G_POLICY_NO,
                        SFPLOCATION:POL_YEAR     = G_YEAR,
                        SFPLOCATION:END_SEQUENCE = G_END_SEQUENCE, Generic

Access SFSLINE, Set SFSLINE:COMPANY_ID       = SFPNAME:COMPANY_ID,
                    SFSLINE:LINE_OF_BUSINESS = L_LINE_OF_BUSINESS,
                    SFSLINE:LOB_SUBLINE      = "00", Exact

Include "swsut100.inc"  --converts the str_state to a 2 digit number uses sfplocation

L_LOB_CODE = SFSLINE:LOB_CODE
I_STATE = BOPGENERAL:STATE
Access SCIPSCONTROL,
       Set SCIPSCONTROL:COMPANY_ID = SFPNAME:COMPANY_ID,
           SCIPSCONTROL:STATE      = I_STATE,
           SCIPSCONTROL:LOB_CODE   = L_LOB_CODE, Exact

/*I added the scipscontrol:insured_mailer_page = "" to make sure that
  it only does the mailing by agent when the the
  scipscontrol:insured_mailer_page = ""
*/

If ((SFPPRINT1:NEW_AGENT_NO = "Y") And
   (L_COPIES_PRINTED = 1)) And 
   (Trun(SCIPSCONTROL:INSURED_MAILER_PAGE) = "") Then
  {
    L_REPORT = "sfpmailer"
    Include "sfsmacro1.inc"
  }
Else  --print the insured mailer page
/*
  08/09/2002 by REL
  I only need to do this once because the program will loop though all the
  mortgagees and also will print the insured right after the invoice are
  printed.  The l_copies_printed is used because I only want to call this once
  per policy numberand not once per copy for each policy number.  Please remenber
  that scipscontrol should not have a value in insured_mailer_page if you do not
  want to mail out policies to the insured and mortgagee.
*/

  If (L_COPIES_PRINTED = 1) And (SCIPSCONTROL:INSURED_MAILER_PAGE <> "") Then
    {
      L_REPORT = Trun(SCIPSCONTROL:INSURED_MAILER_PAGE)
      Include "sfsmacro1.inc"
    }

If SFPMASTER:TRANS_CODE One Of 10 then
    begin 
    if sfpmastsupp:policy_no <> 0 then
        begin
        if SFPMASTSUPP:TERRORISM_PREMIUM <> 0 and
           scipscontrol:dont_print_tpd4_new_business one of 0 Then  --terrorism
      	    {
    	    L_REPORT = "tpd4"
    	    Include "sfsmacro1.inc"
            }
        end
    else
        begin
        if SFPMASTER:TERRORISM_PREMIUM <> 0 and
           scipscontrol:dont_print_tpd4_new_business one of 0 Then  --terrorism
      	    {
    	    L_REPORT = "tpd4"
    	    Include "sfsmacro1.inc"
            }
        end
    end

access sfsmsoterror, set sfsmsoterror:company_id       = sfpname:company_id,
                         sfsmsoterror:state            = i_state,
                         sfsmsoterror:line_of_business = l_line_of_business, generic

l_report = ""
l_report_1 = ""
while sfsmsoterror:company_id = sfpname:company_id and
      sfsmsoterror:state      = i_state and
      sfsmsoterror:line_of_business = l_line_of_business
 	begin
	if (sfpname:eff_date >= sfsmsoterror:eff_date and
           (sfpname:eff_date < sfsmsoterror:exp_date or
           sfsmsoterror:exp_date = 0)) then
            begin
            l_report = sfsmsoterror:tpd_forms_to_print[1]
            l_report_1 = sfsmsoterror:tpd_forms_to_print[2]
            end

	next sfsmsoterror
        end
 
If SFPMASTER:TRANS_CODE = 14 then
    begin 
    if sfpmastsupp:policy_no <> 0 then
        begin
        if sfpmastsupp:terrorism_premium = 0 and
           l_report_1 <> "" then
            begin
    	    l_report = l_report_1  
    	    Include "sfsmacro1.inc"
    	   End
        end
    else
        begin
        if sfpmaster:terrorism_premium = 0 and
           l_report_1 <> "" then
            begin
    	    l_report = l_report_1  
    	    Include "sfsmacro1.inc"
    	   End
        end
    end

If SFPMASTER:TRANS_CODE One Of 14 then
    begin 
    if sfpmastsupp:policy_no <> 0 then
        begin
        if SFPMASTSUPP:TERRORISM_PREMIUM <> 0 Then  --terrorism
       	    begin 
    	    if l_report = "" then 
        	L_REPORT = "tpd5"
    	    Include "sfsmacro1.inc"
    	    end 
	end
    else
        begin
        if SFPMASTER:TERRORISM_PREMIUM <> 0 Then  --terrorism
       	    begin 
    	    if l_report = "" then 
        	L_REPORT = "tpd5"
    	    Include "sfsmacro1.inc"
    	    end 
	end
    end

-- wh16 endorsement changes
If SFPMASTER:TRANS_CODE = 12 Or
   SFPMASTER:TRANS_CODE = 13 Then
    Begin
      L_REPORT = "hopsc16"
      Include "sfsmacro1.inc"
    End

-- dec page

Access SCIPSCONTROL, 
   Set SCIPSCONTROL:COMPANY_ID = L_COMPANY_ID,
       SCIPSCONTROL:STATE      = L_STATE,
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

-- Supplemental Dec Page

if bopgeneral:condo = 0 then
  begin
    If SCIPSCONTROL:USE_BATCH_DEC_PAGE = 1 Then
      Begin
        L_REPORT = Trun(SCIPSCONTROL:BOP_SUPPLEMENTAL_TO_USE)
        Include "sfsmacro1.inc"
      End
    Else
      Begin
        L_REPORT = Trun(SCIPSCONTROL:BOP_SUPPLEMENTAL_TO_USE)
        Include "sfsmacro.inc"
      end
  End
else
    begin
    If SCIPSCONTROL:USE_BATCH_DEC_PAGE = 1 Then
        Begin
        L_REPORT = Trun(SCIPSCONTROL:cpp_dec_page_TO_USE[1])
        Include "sfsmacro1.inc"
        End
    Else
        Begin
        L_REPORT = Trun(SCIPSCONTROL:cpp_dec_page_TO_USE[1])
        Include "sfsmacro.inc"
        end
    End

l_report = ""
-- proxy
If L_COPIES_PRINTED = 1 And
   G_END_SEQUENCE = 0 And
   SCIPSCONTROL:PROXY_TO_PRINT <> "" Then
    Begin
    L_REPORT = SCIPSCONTROL:PROXY_TO_PRINT
    Include "sfsmacro1.inc"
    End

l_report = ""
-- privacy notice

If L_COPIES_PRINTED = 1 And
   SCIPSCONTROL:PRINT_PRIVACY_NOTICE = 1 Then
    Begin
    L_REPORT = "scipspn1"
    Include "sfsmacro1.inc"
    End

-- New Jersey mandatory form

l_report = ""
L_STATE = BOPGENERAL:STATE
L_COMPANY_ID = SFPNAME:COMPANY_ID
L_PARAMETER = "bpsmca301.par"
L_CODE = "MCM820"

Include "sfsbpend.inc"

If L_STATE = 29 And
   G_END_SEQUENCE = 0 And
   L_COPIES_PRINTED = 1 And
   L_PRINT = 1 Then
    Begin
    L_REPORT = "bopmcm820"
    Include "sfsmacro.inc"
    End

l_report = ""
L_CODE = "MCM400"

Include "sfsbpend.inc"

If L_STATE = 29 And
   G_END_SEQUENCE = 0 And
   L_COPIES_PRINTED = 1 And
   L_PRINT = 1 Then
    Begin
    L_REPORT = "bopmcm400"
    Include "sfsmacro.inc"
    End

If SFSCOMPANY:PRINT_ENDORSEMENTS = "Y" Then
  Begin
    Access SFPEND, 
       Set SFPEND:POLICY_NO    = G_POLICY_NO,
           SFPEND:POL_YEAR     = G_YEAR,
           SFPEND:END_SEQUENCE = G_END_SEQUENCE, Approximate

    While sfpend:policy_no = G_policy_no and
          sfpend:pol_year  = G_year and
          sfpend:end_sequence = g_end_sequence
      {
        If SFPEND:OK_PRINT = "Y" Or
           BPSDEFAULT:DONT_PRINT_OPT_END = 0 Then
          {
            Access BOPGENERAL, 
               Set BOPGENERAL:POLICY_NO    = SFPEND:POLICY_NO,
                   BOPGENERAL:POL_YEAR     = SFPEND:POL_YEAR,
                   BOPGENERAL:END_SEQUENCE = SFPEND:END_SEQUENCE,
                   BOPGENERAL:PREM_NO      = SFPEND:PREM_NO,
                   BOPGENERAL:BUILD_NO     = SFPEND:BUILD_NO, Generic

            l_report           = ""
            l_print            = 0  
            L_STATE            = BOPGENERAL:STATE
            L_COMPANY_ID       = SFPNAME:COMPANY_ID
            l_code             = sfpend:code
            L_PREMIUM          = SFPEND:PREMIUM
            l_build_no         = sfpend:build_no
            l_prem_no          = sfpend:prem_no
            Do ACCESS_SFSOPTEND
            do add_and_check_print_array
          }
        next sfpend       
      }
  END
Writefile(L_MACRO,"cli rm %s",Trun(L_MACRO))
closefile(L_MACRO)
If SFSCOMPANY:DEBUG_MODE = 0 Then
  Proc("cli cq %s",Trun(L_MACRO))/noconsole
Else
  Proc("cli cq %s",Trun(L_MACRO))
