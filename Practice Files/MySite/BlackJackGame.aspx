<%@ Page Title ="Play Black Jack" Language="C#" MasterPageFile="~/MasterPage/MasterPage.master" AutoEventWireup="true" CodeFile="BlackJackGame.aspx.cs" Inherits="BlackJackGame" %>

<asp:Content ID="headContent" ContentPlaceHolderID="head" runat="server">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
    <script>
    </script>
</asp:Content>
<asp:Content ID="mainPageContent" ContentPlaceHolderID="pageContent" runat="server">
    <div class ="iframeHolder">
        <div class ="iframeHolderInner">
            <iframe src="https://appetize.io/embed/rq3cxdyyjwpgmk7dvnw2uxq93m?device=nexus5&scale=75&autoplay=false&orientation=portrait&deviceColor=black&screenOnly=true" width="300px" height="597px;" frameborder="0" scrolling="no"></iframe>
        </div>
    </div>
</asp:Content>