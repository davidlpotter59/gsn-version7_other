/* inspection_listing

   scips.com

   july 18, 2002

   inspection listing by date range of inspections not received
*/

define date l_starting_date = parameter/prompt="Enter Starting Date: "
            l_ending_date = parameter/prompt="Enter Ending Date: "
   
define file alt_sfpinspections = access sfpinspections, set
      sfpinspections:policy_no = sfplocation:policy_no,
      sfpinspections:pol_Year = sfplocation:pol_year,
      sfpinspections:end_sequence= sfplocation:end_sequence,
      sfpinspections:prem_no = sfplocation:prem_no,
      sfpinspections:build_no = sfplocation:build_no, generic
                                              
define file alt_sfpname = access sfpname, set
      sfpname:policy_no= sfplocation:policy_no,
      sfpname:pol_Year = sfplocation:pol_year,
      sfpname:end_sequence= sfplocation:end_sequence, generic 

define file alt_sfqinspections = access sfqinspections, set
      sfqinspections:quote_no = alt_sfpname:quote_no,
      sfqinspections:prem_no = sfplocation:prem_no,
      sfqinspections:build_no = sfplocation:build_no, generic
      
define unsigned ascii number l_inspection_co[4] = 
      if alt_sfqinspections:inspection_co <> 0 then
          alt_sfqinspections:inspection_co 
      else                                    
          alt_sfpinspections:inspection_co 
                                              
define file alt_sfsinspect = access sfsinspect, set 
      sfsinspect:company_id = sfpname:company_id,
      sfsinspect:inspection_co = l_inspection_co, generic       
   
where sfplocation:inspection_ordered >= l_starting_date and
      sfplocation:inspection_ordered <= l_ending_date and
      sfplocation:inspection_received = 0 and
      sfplocation:pol_Year = sfpcurrent:pol_year and
      sfplocation:end_sequence = sfpcurrent:end_sequence 

list
/domain="sfplocation"
/nobanner
/duplicates
/title="Inspection's Not Received"

if alt_sfpinspections:request = "Y" or
   alt_sfqinspections:request = "Y" then
    {      
    sfplocation:policy_no/heading="Policy No"
    sfplocation:prem_no/heading="Location No"
    sfplocation:build_no/heading="Building No" 
    sfplocation:inspection_ordered/heading="Date-Inspection-Ordered"                    
    alt_sfsinspect:name[1]/heading="Inspection-Co"/duplicates
    }

sorted by sfplocation:inspection_ordered/newlines=2
          sfplocation:policy_no 
