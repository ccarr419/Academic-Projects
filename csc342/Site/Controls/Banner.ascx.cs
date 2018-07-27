using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Controls_Banner : System.Web.UI.UserControl
{
    public Direction DisplayDirection { get; set; }

    public string NavigateUrl
    {
        get
        {
            object _navigationUrl = ViewState["NavigateUrl"];
            if (_navigationUrl != null)
                return (string)_navigationUrl;
            else
                return "http://p2p.wrox.com"; // Return a default value
        }

        set
        {
            ViewState["NavigateUrl"] = value;
        }
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        switch (DisplayDirection)
        {
            case Direction.Horizontal:
                HorizontalPanel.Visible = true;
                VerticalPanel.Visible = false;
                HorizontalLink.HRef = NavigateUrl;
                break;
            case Direction.Vertical:
                VerticalPanel.Visible = true;
                HorizontalPanel.Visible = false;
                VerticalLink.HRef = NavigateUrl;
                break;
        }
    }
}