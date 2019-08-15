/* summary_detail_loss.eq

   SCIPS.com

   December 9, 2004

   show where summary and detail are out of balance for loss resv and loss paid
*/

description Report to show where summary and detail are out of balance for loss resv and loss paid ;
  
define file lrsdetaila = access lrsdetail, 

set lrsdetail:company_id = lrssummary:company_id,

    lrsdetail:claim_no   = lrssummary:claim_no, one to many, generic 

 

define signed ascii number l_loss_reserv = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10))) 

then lrsdetaila:loss_resv 

else 0.00

 

define signed ascii number l_loss_paid = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10)))

then lrsdetaila:loss_paid  

else 0.00


list

/nobanner

/domain="lrssummary"

/nodetail 

/title="Summary to Detail Balance Issues - Loss"

/nototals 

/pagelength=0

/pagewidth=255   

 

lrssummary:claim_no/column=1

lrssummary:loss_resv/column=10/heading="Lrssummary-Loss Resv"

l_loss_reserv/column=30/heading="Lrsdetail-Loss Resv"

lrssummary:loss_paid/column=50/heading="Lrssummary-Loss Paid"

l_loss_paid/column=70/heading="Lrsdetail-Loss Paid"    
 

sorted by lrssummary:claim_no 

                                                         
end of report

   total[lrssummary:loss_resv]/column=10

   total[l_loss_reserv]/column=30

   total[lrssummary:loss_paid]/column=50

   total[l_loss_paid]/column=70 

end of lrssummary:claim_no             
box/noblanklines/noheadings 

if total[lrssummary:loss_resv ] <> total[l_loss_reserv] or 

   total[lrssummary:loss_paid]  <> total[l_loss_paid] then 

{

   lrssummary:claim_no /column=1

   total[lrssummary:loss_resv]/column=10

   total[l_loss_reserv]/column=30

   total[lrssummary:loss_paid]/column=50

   total[l_loss_paid]/column=70                      
 

   if total[lrssummary:loss_resv] <> total[l_loss_reserv] then 

   {

     "Reserves out of balance"/column=100

   }

   if total[lrssummary:loss_paid] <> total[l_loss_paid] then 

   {

     "Payments out of balance"/column=130

   }

 

}

end box

 
