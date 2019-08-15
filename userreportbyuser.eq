/* userreportbyuser.eq

   scips.com

   April 5, 2002

   report listing what rater did what policy by trans date
*/

description Rater Policy Listing ;

define date l_starting_date = parameter/prompt="Enter Starting Date: "
            l_ending_date = parameter/prompt="Enter Ending Date: "

define string l_user_id = parameter/prompt="Enter User ID: "

where sfpname:trans_date >= l_starting_date and
      sfpname:trans_date <= l_ending_date and
      sfpname:user_id = l_User_id
list
/domain="sfpmaster"
/nobanner

sfpname:policy_no
sfpname:pol_year
sfpname:end_sequence       
sfpmaster:trans_code
sfpname:convert_date
sfpname:convert_time

sorted by sfpmaster:trans_code/newlines=2
          sfpmaster:policy_no
         
end of sfpmaster:trans_code
""/newline
count[sfpname:policy_no]/heading="Total Number Of Policies By Trans Code"

top of page
sfpname:user_id/heading="Rater"/newline

end of report                                              
""/newline
count[sfpmaster:policy_no]/heading="Total Number Of Policies"
