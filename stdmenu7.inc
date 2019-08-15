/*  stdmenu7.inc

    March 16, 2005

    SCIPS.com, Inc.

    Standard menu items for SCIPS Version 7
*/

Menubar
{
    Menu Tagged File_mm Properties { Text="File" }
    {    
	    Menuitem Properties {
					    Iconname = "add.bmp"
					    Text     = "Add New Record"
					    Shortcut = "F5" 
					    }
                  Events     {
					    Action   = Add_fn
					    }
         Menuitem Properties {
					    Iconname = "change.bmp"
					    Text     = "Change Current Record"
					    Shortcut = "F6" 
					    }
                  Events     {
					    Action   = Change_fn
					    }
         Menuitem Properties {
					    Iconname = "delete.bmp"
					    Text     = "Delete Current Record"
					    Shortcut = "Shift+F6" 
					    }
                  Events     {
					    Action   = Delete_fn
					    }
     Separator
         Menuitem Properties {
					    Iconname = "printer.bmp"
					    Text     = "Print Screen"
					    Shortcut = "Ctrl+P" 
					    }
                  Events     {
					    Action   = Print_fn
					    }
     Separator
         Menuitem Properties {
					    Iconname = "exit.bmp"
					    Text     = "Exit Screen"
					    Shortcut = "F10" 
					    }
                  Events     {
					    Action   = Exit_fn
					    }
     }
    Menu Tagged File_mm Properties { Text="Edit" }
    {    
	    Menuitem Properties {
					    Iconname = "search.bmp"
					    Text     = "Search for Record"
					    Shortcut = "F3" 
					    }
                  Events     {
					    Action   = Search_fn
					    }
	    Menuitem Properties {
					    Iconname = "next.bmp"
					    Text     = "Next Record"
					    Shortcut = "F7" 
					    }
                  Events     {
					    Action   = Next_fn
					    }
	    Menuitem Properties {
					    Iconname = "previous.bmp"
					    Text     = "Previous Record"
					    Shortcut = "F8" 
					    }
                  Events     {
					    Action   = Previous_fn
					    }
    }
}
