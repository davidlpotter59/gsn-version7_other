define file sfsagent_alias = access sfsagent,
                                set sfsagent:company_id = sfpname:company_id, 
                                    sfsagent:agent_no   = sfpname:agent_no, generic 

define file sfsline_alias = access sfsline,
                               set sfsline:company_id       = sfpname:company_id,
                                   sfsline:line_of_business = sfpname:line_of_business,
                                   sfsline:lob_subline      = "00", exact

define string I_name[50] = sfpname:name[1]
define string I_name1[50] = sfpname:name[2]
define string l_policy_no[9] = str(sfpname:policy_no)


include "startend.inc"
include "renaeq1.inc"
DEFINE STRING
        I_REV_NAME1[50] =
        TRUN(I_NAME1[(POS("=",I_NAME1)+1),
        LEN(I_NAME1)])+" "+TRUN(I_NAME1[0,(POS("=",I_NAME1)-1)])

where sfpname:trans_date >= l_starting_date
     and sfpname:trans_date <= l_ending_date 

list

/domain="sfpcurrent"
/noheadings
/nobanner
/nodefaults
/pagelength= 0  

"Policy Drawer"/column=1   
str(l_policy_no)/column=21
I_REV_NAME + " " + I_rev_name1 + " " + sfpname:name[3]/column=41
trun(sfsline_alias:alpha)+str(l_policy_no)/column=599 
"Policy File"/column=671

