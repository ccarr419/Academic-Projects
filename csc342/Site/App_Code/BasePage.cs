using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public class BasePage : System.Web.UI.Page
{
    private void Page_PreInit(object sender, EventArgs e)
    {
        HttpCookie preferredTheme = Request.Cookies.Get("PreferredTheme");
        if(preferredTheme != null)
        {
            string folder = Server.MapPath("-App_Themes/" + preferredTheme.Value);
            if(System.IO.Directory.Exists(folder))
            {
                Page.Theme = preferredTheme.Value;
            }
        }
    }

    private void Page_PreRender(object sender, EventArgs e)
    {
        if(string.IsNullOrEmpty(this.Title) || this.Title.Equals("Untitled Page",
                    StringComparison.CurrentCultureIgnoreCase))
        {
            throw new Exception(
                "Page title cannot be \"Untitled\" or an empty string.");
        }
    }

    public BasePage()
    {
        this.PreRender += Page_PreRender;
        this.PreInit += Page_PreInit;
    }
}