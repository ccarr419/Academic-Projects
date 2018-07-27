<%@ Page Title="Web Services Demo" Language="C#" MasterPageFile="~/MasterPages/Frontend.master" AutoEventWireup="true" CodeFile="WebServices.aspx.cs" Inherits="Demos_WebServices" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cpMainContent" Runat="Server">
    <asp:ScriptManager ID="ScriptManagerProxy1" runat="server">
        <Services>
            <asp:ServiceReference Path="~/WebServices/NameService.svc" />
        </Services>
    </asp:ScriptManager>       
    <asp:TextBox ID="YourName" runat="server"></asp:TextBox>
    <asp:Button ID="SayHello" runat="server" Text="Button" value="Say Hello" OnClick="helloWorld();" />
    <script type="text/javascript">
        function helloWorld()
        {
            var yourName = document.getElementById('YourName').value;
            NameService.helloWorld(yourName, helloWorldCallback);
        }
        function helloWorldCallback(result)
        {
            alert(result);
        }
    </script>
</asp:Content>

