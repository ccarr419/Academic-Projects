<%@ Page Title ="Welcome To My Site" Language="C#" MasterPageFile="~/MasterPage/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<asp:Content ID="headContent" ContentPlaceHolderID="head" runat="server">
    <script>
    </script>
</asp:Content>
<asp:Content ID="headImage" ContentPlaceHolderID="pageHeaderImage" runat="server">
</asp:Content>
<asp:Content ID="mainPageContent" ContentPlaceHolderID="pageContent" runat="server">
    <table class="centeredTable">
        <tr>
            <td class="menuOption">New Game</td>
        </tr>
        <tr>
            <td class="menuOption">Load Game</td>
        </tr>
        <tr>
            <td class="menuOption">Options</td>
        </tr>
    </table>
</asp:Content>
