/*  stdtoolbar7.inc

    March 16, 2005

    SCIPS.com, Inc.

    Standard tool bar items for SCIPS Version 7
*/

Toolbar Tagged Main_t Properties
				  {
				      Text = "Main"
					 FontName = "SansSerif"
					 Fontsize = 10
				  }
			{
		     ToolBarButton
				  Properties
				  {
			     	 Iconname   = "search.bmp"
				  }
				  Events     
				  {
			         	 Action = Search_fn
			       }
               Separator
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "previous.bmp"
				  }
				  Events     
				  {
			           Action = previous_fn
			       }
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "next.bmp"
				  }
				  Events     
				  {
			           Action = next_fn
                      }
               Separator
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "add.bmp"
				  }
				  Events     
				  {
			           Action = add_fn
                      }
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "change.bmp"
				  }
				  Events     
				  {
			           Action = change_fn
                      }
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "delete.bmp"
				  }
				  Events     
				  {
			           Action = delete_fn
                      }
                Separator
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "printer.bmp"
				  }
				  Events     
				  {
			           Action = print_fn
                      }
                Separator
			    	  ToolbarButton 
				  Properties
				  {
					 ToolTip = "OK - Accept Changes/Updates"
                      }
				  Events 
				  { 
				      Action = Autoupdate 
		            }               
				  ToolbarButton 
				  Properties
				  {
					 ToolTip = "Cancel Current Transaction"
                      }
				  Events 
				  { 
					 Action =  Cancel 
		            }                  
				  ToolbarButton 
				  Properties
				  {
					 Tooltip = "Abort Current Transaction"
                      }
				  Events 
				  { 
					 Action =  Abort 
		            }                  
                Separator
		     ToolBarButton
				  Properties
				  {
				      Iconname   = "exit.bmp"
				      fontsize   = 12	
				  }
				  Events     
				  {
			           Action = exit_fn
				  }

                 }
