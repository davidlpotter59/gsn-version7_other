/*
Quote To Policy Listing

SCIPS.com, Inc.

September 12, 2012

Report to list quote numbers with the corresponding policy number
*/
Description
Report lists all quote numbers within the dates range with the corresponding policy number listed;

include "startend.inc"

where sfqname:eff_date    >= l_starting_date and
      sfqname:eff_date    <= l_ending_date 

list
/nobanner
/domain="sfqname"
/title="Quote to Policy LIsting"

quote_no policy_no eff_date exp_date line_of_business name agent_no 
sorted by sfqname:quote_no 
          sfqname:eff_date 
          sfqname:line_of_business 
          sfqname:agent_no

