Hello there! it's a qt6 project about a simple addressbook.
ide: qt6;
os: windows11;

function: local sqlite3 datanase storeing contacts, folder pic stores the related avatar. you can add,modify,delete contact through this application.

SqlDriver: the sqldriver is sqlitecipher, i set the original pwd for connecting databse as "sa".

About the File:  the sqlite folder is source code.
                 and build folder is deployed click run-able app.

Database Structure: 
                    database---addressbook.sqlite3|->table---login(for login)
                                                  |->table---contact(storing contact)
                                                         
                    table|---login->name string;
                         |        ->password string;
                         | 
                         |---contact->name  
                                   ->phone
                                   ->email
                                   ->address

main item used in qt is listwidget, first u need rigister. after log in, right clicked the center, u can delete and modify contact.
top-left u can choose to sort contact by time or alphabet. each new contact added, u need to choose top-left time or alphabet to update the listWidget.
i try to use a timer to update automaticlly, but cpu highly used. top-right u can pin the window on the top. but can't change it back.i don't know how.

u can do waht u  want to the source code.
if u have funny stuff, share!

that's it!! a simple one for coder!! 
just a beginning.

cheers :)
