description This will be used by imageright to create a templete for each policy.  FUP upload;
define file sfsagent_alias = access sfsagent,
                                set sfsagent:company_id = sfpname:company_id, 
                                    sfsagent:agent_no   = sfpname:agent_no, generic 

define file sfsline_alias = access sfsline,
                               set sfsline:company_id       = sfpname:company_id,
                                   sfsline:line_of_business = sfpname:line_of_business,
                                   sfsline:lob_subline      = "00", exact

define file sfsline2_alias = access sfsline2,
                                set sfsline2:company_id       = sfpname:company_id,
                                    sfsline2:line_of_business = sfpname:line_of_business,
                                    sfsline2:lob_subline      = "00", exact


define string I_name[50] = sfpname:name[1]
define string I_name1[50] = sfpname:name[2]
define string l_policy_no[9] = str(sfpname:policy_no)
define string full_policy_no[15] = if trun(sfsline2_alias:ADDITIONAL_ALPHA_PREFIX) = "" then 
                                     trun(sfsline_alias:alpha)+str(l_policy_no)
                                   else
                                     trun(sfsline2_alias:ADDITIONAL_ALPHA_PREFIX)+str(l_policy_no)  

--include "startend.inc"

include "renaeq1.inc"
DEFINE STRING
        I_REV_NAME1[50] =
        TRUN(I_NAME1[(POS("=",I_NAME1)+1),
        LEN(I_NAME1)])+" "+TRUN(I_NAME1[0,(POS("=",I_NAME1)-1)])

where sfpname:trans_date >= todaysdate    --l_starting_date 
     and sfpname:trans_date <= todaysdate --l_ending_date  

list
/domain="sfpcurrent"
/noheadings
/banner
/text
/nodefaults
/pagelength= 0  
/pagewidth=1050


"Policy Drawer"/column=1   
full_policy_no/column=21
I_REV_NAME + " " + I_rev_name1 + " " + sfpname:name[3]/column=41
"        "/column=196 
"                                        "/column=204
"Agency Code=" + str(sfpname:agent_no)/column=244
"Line of Business=" + str(sfpname:line_of_business)/column=294
"Effective Date=" + str(sfpname:eff_date,"MM-DD-YYYY")/column=344
if sfpname:status="CURRENT" and 
   sfpname:eff_date <= 10.16.2008 then
  {
    "Status=" + "EXPIRED"/NOHEADING/column=394
  }
ELSE
  {
    "Status=" + SFPNAME:STATUS/NOHEADING/column=394
  }
if trun(sfpname:address[3]) <> "" then
  {
    "Mailing Address=" + trun(sfpname:address[1]) + ", " + trun(sfpname:address[2]) + ", " + trun(sfpname:address[3]) + ", "
 + 
                         trun(sfpname:city) + ", " + trun(sfpname:str_state) + " " + trun(sfpname:str_zipcode)/column=444
  }
else
  if Trun(sfpname:address[2]) <> "" then
    {
      "Mailing Address=" + trun(sfpname:address[1]) + ", " + trun(sfpname:address[2]) + ", " + 
                           trun(sfpname:city) + ", " + trun(sfpname:str_state) + " " + trun(sfpname:str_zipcode)/column=444
    }
  else
    {
      "Mailing Address=" + trun(sfpname:address[1]) + ", " + 
                   trun(sfpname:city) + ", " + trun(sfpname:str_state) + " " + trun(sfpname:str_zipcode)/column=444
    }

"Policy File"/column=671/newline
"Policy Drawer"/column=1 
full_policy_no/column= 21   
I_REV_NAME + " " + i_rev_name1 + " " + sfpname:name[3]/column=41 
"Agency Name=" + sfsagent_alias:name[1]/column=444
"Policy File"/column=671
