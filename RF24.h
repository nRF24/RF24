




<!DOCTYPE html>
<html class="   ">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    
    
    <title>RF24/RF24.h at master · TMRh20/RF24</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub">
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub">
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png">
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png">
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png">
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png">
    <meta property="fb:app_id" content="1401488693436528">

      <meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="TMRh20/RF24" name="twitter:title" /><meta content="Optimized fork of nRF24L01 for Arduino and Raspberry Pi" name="twitter:description" /><meta content="https://avatars3.githubusercontent.com/u/2610460?v=1&amp;s=400" name="twitter:image:src" />
<meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="https://avatars3.githubusercontent.com/u/2610460?v=1&amp;s=400" property="og:image" /><meta content="TMRh20/RF24" property="og:title" /><meta content="https://github.com/TMRh20/RF24" property="og:url" /><meta content="Optimized fork of nRF24L01 for Arduino and Raspberry Pi" property="og:description" />

    <link rel="assets" href="https://assets-cdn.github.com/">
    <link rel="conduit-xhr" href="https://ghconduit.com:25035">
    <link rel="xhr-socket" href="/_sockets">

    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="selected-link" value="repo_source" data-pjax-transient>
      <meta name="google-analytics" content="UA-3769691-2">

    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="AF8EE9B5:6942:B4DED33:53DF2AD7" name="octolytics-dimension-request_id" /><meta content="539857" name="octolytics-actor-id" /><meta content="stanleyseow" name="octolytics-actor-login" /><meta content="a8e79e6be21d3d96d6758fbbbd41706d09d3d9abe9313e40b002417705fcb09e" name="octolytics-actor-hash" />
    

    
    
    <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico">


    <meta content="authenticity_token" name="csrf-param" />
<meta content="vP+51/P7jc+H124MugZyeQbXOzCE3+9IBz//Hl68dGWRrNDqgfC7vFAsbBsENeb8D3yNyGkNJ339s7ufr3JBDA==" name="csrf-token" />

    <link href="https://assets-cdn.github.com/assets/github-8488336393a59083828e685a8702f8734352719a.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://assets-cdn.github.com/assets/github2-6f603f8712a3ad84b467294bd7ff80bafef0dfa6.css" media="all" rel="stylesheet" type="text/css" />
    


    <meta http-equiv="x-pjax-version" content="b97903e118817dc3b1b23f8b995593f2">

      
  <meta name="description" content="Optimized fork of nRF24L01 for Arduino and Raspberry Pi">


  <meta content="2610460" name="octolytics-dimension-user_id" /><meta content="TMRh20" name="octolytics-dimension-user_login" /><meta content="17856505" name="octolytics-dimension-repository_id" /><meta content="TMRh20/RF24" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="true" name="octolytics-dimension-repository_is_fork" /><meta content="1498978" name="octolytics-dimension-repository_parent_id" /><meta content="maniacbug/RF24" name="octolytics-dimension-repository_parent_nwo" /><meta content="1498978" name="octolytics-dimension-repository_network_root_id" /><meta content="maniacbug/RF24" name="octolytics-dimension-repository_network_root_nwo" />

  <link href="https://github.com/TMRh20/RF24/commits/master.atom" rel="alternate" title="Recent Commits to RF24:master" type="application/atom+xml">

  </head>


  <body class="logged_in  env-production macintosh vis-public fork page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>
    <div class="wrapper">
      
      
      
      


      <div class="header header-logged-in true">
  <div class="container clearfix">

    <a class="header-logo-invertocat" href="https://github.com/" aria-label="Homepage">
  <span class="mega-octicon octicon-mark-github"></span>
</a>


    
    <a href="/notifications" aria-label="You have unread notifications" class="notification-indicator tooltipped tooltipped-s" data-hotkey="g n">
        <span class="mail-status unread"></span>
</a>

      <div class="command-bar js-command-bar  in-repository">
          <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<div class="commandbar">
  <span class="message"></span>
  <input type="text" data-hotkey="s, /" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    data-username="stanleyseow"
    data-repo="TMRh20/RF24"
  >
  <div class="display hidden"></div>
</div>

    <input type="hidden" name="nwo" value="TMRh20/RF24">

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target" role="button" aria-haspopup="true">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container" aria-hidden="true">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked">
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global">
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="help tooltipped tooltipped-s" aria-label="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
        <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
            <li><a href="https://gist.github.com">Gist</a></li>
            <li><a href="/blog">Blog</a></li>
          <li><a href="https://help.github.com">Help</a></li>
        </ul>
      </div>

    

<ul id="user-links">
  <li>
    <a href="/stanleyseow" class="name">
      <img alt="Stanley Seow" data-user="539857" height="20" src="https://avatars2.githubusercontent.com/u/539857?v=1&amp;s=40" width="20" /> stanleyseow
    </a>
  </li>

  <li class="new-menu dropdown-toggle js-menu-container">
    <a href="#" class="js-menu-target tooltipped tooltipped-s" aria-label="Create new...">
      <span class="octicon octicon-plus"></span>
      <span class="dropdown-arrow"></span>
    </a>

    <div class="new-menu-content js-menu-content">
    </div>
  </li>

  <li>
    <a href="/settings/profile" id="account_settings"
      class="tooltipped tooltipped-s"
      aria-label="Account settings ">
      <span class="octicon octicon-tools"></span>
    </a>
  </li>
  <li>
    <form accept-charset="UTF-8" action="/logout" class="logout-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="4qLWca/DczkzLYqimASdisGG9nRl/0ALcMej82ty6ShlTIUSzTzMN+JlJ94mdnrl8iXX8oAU9/qye3Mg5CXhsw==" /></div>
      <button class="sign-out-button tooltipped tooltipped-s" aria-label="Sign out">
        <span class="octicon octicon-sign-out"></span>
      </button>
</form>  </li>

</ul>

<div class="js-new-dropdown-contents hidden">
  

<ul class="dropdown-menu">
  <li>
    <a href="/new"><span class="octicon octicon-repo"></span> New repository</a>
  </li>
  <li>
    <a href="https://porter.github.com/new"><span class="octicon octicon-move-right"></span> Import repository</a>
  </li>
  <li>
    <a href="/organizations/new"><span class="octicon octicon-organization"></span> New organization</a>
  </li>


    <li class="section-title">
      <span title="TMRh20/RF24">This repository</span>
    </li>
      <li>
        <a href="/TMRh20/RF24/issues/new"><span class="octicon octicon-issue-opened"></span> New issue</a>
      </li>
</ul>

</div>


    
  </div>
</div>

      

        



      <div id="start-of-content" class="accessibility-aid"></div>
          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    <div id="js-flash-container">
      
    </div>
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        
<ul class="pagehead-actions">

    <li class="subscription">
      <form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="8U6bJZB4LijnnB8tdu+iWbQLKeWmd4IXtdlDkDlbrtuChb6hWRnBnOAkogE7W/Pc45SSrlDVb8PI4B6FWhFrQw==" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="17856505" />

    <div class="select-menu js-menu-container js-select-menu">
      <a class="social-count js-social-count" href="/TMRh20/RF24/watchers">
        16
      </a>
      <a href="/TMRh20/RF24/subscription"
        class="minibutton select-menu-button with-count js-menu-target" role="button" tabindex="0" aria-haspopup="true">
        <span class="js-select-button">
          <span class="octicon octicon-eye"></span>
          Watch
        </span>
      </a>

      <div class="select-menu-modal-holder">
        <div class="select-menu-modal subscription-menu-modal js-menu-content" aria-hidden="true">
          <div class="select-menu-header">
            <span class="select-menu-title">Notifications</span>
            <span class="octicon octicon-x js-menu-close" role="button" aria-label="Close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-list js-navigation-container" role="menu">

            <div class="select-menu-item js-navigation-item selected" role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input checked="checked" id="do_included" name="do" type="radio" value="included" />
                <h4>Not watching</h4>
                <span class="description">Be notified when participating or @mentioned.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye"></span>
                  Watch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_subscribed" name="do" type="radio" value="subscribed" />
                <h4>Watching</h4>
                <span class="description">Be notified of all conversations.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye"></span>
                  Unwatch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item " role="menuitem" tabindex="0">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_ignore" name="do" type="radio" value="ignore" />
                <h4>Ignoring</h4>
                <span class="description">Never be notified.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-mute"></span>
                  Stop ignoring
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

</form>
    </li>

  <li>
    

  <div class="js-toggler-container js-social-container starring-container ">

    <form accept-charset="UTF-8" action="/TMRh20/RF24/unstar" class="js-toggler-form starred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="pu3MxdhdcDzJIvV/sp8JRhOt+pDElKAIhRpnFQ10pjIeFlRKCZoCUSddIaUJnhZ4mrtJHeA+7CpcEFh6qjqwIQ==" /></div>
      <button
        class="minibutton with-count js-toggler-target star-button"
        aria-label="Unstar this repository" title="Unstar TMRh20/RF24">
        <span class="octicon octicon-star"></span>
        Unstar
      </button>
        <a class="social-count js-social-count" href="/TMRh20/RF24/stargazers">
          54
        </a>
</form>
    <form accept-charset="UTF-8" action="/TMRh20/RF24/star" class="js-toggler-form unstarred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="Kz6FQIE/Jto3b9zPpW4CP8fByYTZBz0KetpKzaSw6u9DtyqV9kOU7wsBp5rJDHa5SfkZuB71d04ElviEzqogvg==" /></div>
      <button
        class="minibutton with-count js-toggler-target star-button"
        aria-label="Star this repository" title="Star TMRh20/RF24">
        <span class="octicon octicon-star"></span>
        Star
      </button>
        <a class="social-count js-social-count" href="/TMRh20/RF24/stargazers">
          54
        </a>
</form>  </div>

  </li>


        <li>
          <a href="/TMRh20/RF24/fork" class="minibutton with-count js-toggler-target fork-button lighter tooltipped-n" title="Fork your own copy of TMRh20/RF24 to your account" aria-label="Fork your own copy of TMRh20/RF24 to your account" rel="nofollow" data-method="post">
            <span class="octicon octicon-repo-forked"></span>
            Fork
          </a>
          <a href="/TMRh20/RF24/network" class="social-count">273</a>
        </li>

</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="mega-octicon octicon-repo-forked"></span>
          <span class="author"><a href="/TMRh20" class="url fn" itemprop="url" rel="author"><span itemprop="title">TMRh20</span></a></span><!--
       --><span class="path-divider">/</span><!--
       --><strong><a href="/TMRh20/RF24" class="js-current-repository js-repo-home-link">RF24</a></strong>

          <span class="page-context-loader">
            <img alt="" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

            <span class="fork-flag">
              <span class="text">forked from <a href="/maniacbug/RF24">maniacbug/RF24</a></span>
            </span>
        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      <div class="repository-with-sidebar repo-container new-discussion-timeline  ">
        <div class="repository-sidebar clearfix">
            

<div class="sunken-menu vertical-right repo-nav js-repo-nav js-repository-container-pjax js-octicon-loaders" data-issue-count-url="/TMRh20/RF24/issues/counts">
  <div class="sunken-menu-contents">
    <ul class="sunken-menu-group">
      <li class="tooltipped tooltipped-w" aria-label="Code">
        <a href="/TMRh20/RF24" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-hotkey="g c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /TMRh20/RF24">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped tooltipped-w" aria-label="Issues">
          <a href="/TMRh20/RF24/issues" aria-label="Issues" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g i" data-selected-links="repo_issues repo_labels repo_milestones /TMRh20/RF24/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class="js-issue-replace-counter"></span>
            <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped tooltipped-w" aria-label="Pull Requests">
        <a href="/TMRh20/RF24/pulls" aria-label="Pull Requests" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g p" data-selected-links="repo_pulls /TMRh20/RF24/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class="js-pull-replace-counter"></span>
            <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


    </ul>
    <div class="sunken-menu-separator"></div>
    <ul class="sunken-menu-group">

      <li class="tooltipped tooltipped-w" aria-label="Pulse">
        <a href="/TMRh20/RF24/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="pulse /TMRh20/RF24/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Graphs">
        <a href="/TMRh20/RF24/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_graphs repo_contributors /TMRh20/RF24/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

              <div class="only-with-full-nav">
                

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="input-group">
    <input type="text" class="input-mini input-monospace js-url-field"
           value="https://github.com/TMRh20/RF24.git" readonly="readonly">
    <span class="input-group-button">
      <button aria-label="Copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/TMRh20/RF24.git" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="ssh"
  data-url="/users/set_protocol?protocol_selector=ssh&amp;protocol_type=clone">
  <h3><strong>SSH</strong> clone URL</h3>
  <div class="input-group">
    <input type="text" class="input-mini input-monospace js-url-field"
           value="git@github.com:TMRh20/RF24.git" readonly="readonly">
    <span class="input-group-button">
      <button aria-label="Copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="git@github.com:TMRh20/RF24.git" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="input-group">
    <input type="text" class="input-mini input-monospace js-url-field"
           value="https://github.com/TMRh20/RF24" readonly="readonly">
    <span class="input-group-button">
      <button aria-label="Copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/TMRh20/RF24" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
      <a href="#" class="js-clone-selector" data-protocol="ssh">SSH</a>,
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <a href="https://help.github.com/articles/which-remote-url-should-i-use" class="help tooltipped tooltipped-n" aria-label="Get help on which URL is right for you.">
    <span class="octicon octicon-question"></span>
  </a>
</p>

  <a href="http://mac.github.com" data-url="github-mac://openRepo/https://github.com/TMRh20/RF24" class="minibutton sidebar-button js-conduit-rewrite-url" title="Save TMRh20/RF24 to your computer and use it in GitHub Desktop." aria-label="Save TMRh20/RF24 to your computer and use it in GitHub Desktop.">
    <span class="octicon octicon-device-desktop"></span>
    Clone in Desktop
  </a>


                <a href="/TMRh20/RF24/archive/master.zip"
                   class="minibutton sidebar-button"
                   aria-label="Download TMRh20/RF24 as a zip file"
                   title="Download TMRh20/RF24 as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
              </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<a href="/TMRh20/RF24/blob/327f0609cf7b52b70accccc175b5809dd5074704/RF24.h" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:99471240b688d1328afc4a8afe2c8936 -->

<div class="file-navigation">
  

<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target css-truncate" data-hotkey="w"
    data-master-branch="master"
    data-ref="master"
    title="master"
    role="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button css-truncate-target">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-x js-menu-close" role="button" aria-label="Close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/arduino-1.0/RF24.h"
                 data-name="arduino-1.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="arduino-1.0">arduino-1.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/gh-pages/RF24.h"
                 data-name="gh-pages"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="gh-pages">gh-pages</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/interrupts/RF24.h"
                 data-name="interrupts"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="interrupts">interrupts</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/master/RF24.h"
                 data-name="master"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="master">master</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/p_enable/RF24.h"
                 data-name="p_enable"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="p_enable">p_enable</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/write_bug/RF24.h"
                 data-name="write_bug"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="write_bug">write_bug</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="button-group right">
    <a href="/TMRh20/RF24/find/master"
          class="js-show-file-finder minibutton empty-icon tooltipped tooltipped-s"
          data-pjax
          data-hotkey="t"
          aria-label="Quickly jump between files">
      <span class="octicon octicon-list-unordered"></span>
    </a>
    <button class="js-zeroclipboard minibutton zeroclipboard-button"
          data-clipboard-text="RF24.h"
          aria-label="Copy to clipboard"
          data-copied-hint="Copied!">
      <span class="octicon octicon-clippy"></span>
    </button>
  </div>

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/TMRh20/RF24" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">RF24</span></a></span></span><span class="separator"> / </span><strong class="final-path">RF24.h</strong>
  </div>
</div>


  <div class="commit file-history-tease">
      <img alt="TMRh20" class="main-avatar" data-user="2610460" height="24" src="https://avatars1.githubusercontent.com/u/2610460?v=1&amp;s=48" width="24" />
      <span class="author"><a href="/TMRh20" rel="author">TMRh20</a></span>
      <time datetime="2014-07-31T00:49:45-06:00" is="relative-time">July 31, 2014</time>
      <div class="commit-title">
          <a href="/TMRh20/RF24/commit/327f0609cf7b52b70accccc175b5809dd5074704" class="message" data-pjax="true" title="Add optional write timeout/failure handling

Per issue #5 by sven337
- Add optional failure handling/timeout
- Un-comment #define FAILURE_HANDLING in RF24_config.h to enable
- Add radio.errorDetected variable - indicates if an error/timeout was
detected
example:
if(radio.failureDetected){
delay(1000);
radio.begin();
radio.failureDetected = 0;
radio.openWritingPipe(addresses[1]);
radio.openReadingPipe(1,addresses[0]);
report_failure(); //blink leds, send a message, etc.
}

Additional:
- removed unused wide_band boolean
- remove rx buffer flushes for RPi also">Add optional write timeout/failure handling</a>
      </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>4</strong>  contributors</a></p>
          <a class="avatar tooltipped tooltipped-s" aria-label="maniacbug" href="/TMRh20/RF24/commits/master/RF24.h?author=maniacbug"><img alt="maniacbug" data-user="636684" height="20" src="https://avatars0.githubusercontent.com/u/636684?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="TMRh20" href="/TMRh20/RF24/commits/master/RF24.h?author=TMRh20"><img alt="TMRh20" data-user="2610460" height="20" src="https://avatars3.githubusercontent.com/u/2610460?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="gcopeland" href="/TMRh20/RF24/commits/master/RF24.h?author=gcopeland"><img alt="gcopeland" data-user="310269" height="20" src="https://avatars2.githubusercontent.com/u/310269?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="a-lurker" href="/TMRh20/RF24/commits/master/RF24.h?author=a-lurker"><img alt="a-lurker" data-user="7496794" height="20" src="https://avatars3.githubusercontent.com/u/7496794?v=1&amp;s=40" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list">
          <li class="facebox-user-list-item">
            <img alt="maniacbug" data-user="636684" height="24" src="https://avatars2.githubusercontent.com/u/636684?v=1&amp;s=48" width="24" />
            <a href="/maniacbug">maniacbug</a>
          </li>
          <li class="facebox-user-list-item">
            <img alt="TMRh20" data-user="2610460" height="24" src="https://avatars1.githubusercontent.com/u/2610460?v=1&amp;s=48" width="24" />
            <a href="/TMRh20">TMRh20</a>
          </li>
          <li class="facebox-user-list-item">
            <img alt="gcopeland" data-user="310269" height="24" src="https://avatars0.githubusercontent.com/u/310269?v=1&amp;s=48" width="24" />
            <a href="/gcopeland">gcopeland</a>
          </li>
          <li class="facebox-user-list-item">
            <img alt="a-lurker" data-user="7496794" height="24" src="https://avatars1.githubusercontent.com/u/7496794?v=1&amp;s=48" width="24" />
            <a href="/a-lurker">a-lurker</a>
          </li>
      </ul>
    </div>
  </div>

<div class="file-box">
  <div class="file">
    <div class="meta clearfix">
      <div class="info file-name">
          <span>1217 lines (1104 sloc)</span>
          <span class="meta-divider"></span>
        <span>41.714 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
          <a href="/TMRh20/RF24/raw/master/RF24.h" class="minibutton " id="raw-url">Raw</a>
            <a href="/TMRh20/RF24/blame/master/RF24.h" class="minibutton js-update-url-with-hash">Blame</a>
          <a href="/TMRh20/RF24/commits/master/RF24.h" class="minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->

          <a class="octicon-button tooltipped tooltipped-nw js-conduit-openfile-check"
             href="http://mac.github.com"
             data-url="github-mac://openRepo/https://github.com/TMRh20/RF24?branch=master&amp;filepath=RF24.h"
             aria-label="Open this file in GitHub for Mac"
             data-failed-title="Your version of GitHub for Mac is too old to open this file. Try checking for updates.">
              <span class="octicon octicon-device-desktop"></span>
          </a>

              <a class="octicon-button tooltipped tooltipped-n js-update-url-with-hash"
                 aria-label="Clicking this button will fork this project so you can edit the file"
                 href="/TMRh20/RF24/edit/master/RF24.h"
                 data-method="post" rel="nofollow"><span class="octicon octicon-pencil"></span></a>

            <a class="octicon-button danger tooltipped tooltipped-s"
               href="/TMRh20/RF24/delete/master/RF24.h"
               aria-label="Fork this project and delete file"
               data-method="post" data-test-id="delete-blob-file" rel="nofollow">
          <span class="octicon octicon-trashcan"></span>
        </a>
      </div><!-- /.actions -->
    </div>
      
  <div class="blob-wrapper data type-c">
       <table class="file-code file-diff tab-size-8">
         <tr class="file-code-line">
           <td class="blob-line-nums">
             <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>
<span id="L345" rel="#L345">345</span>
<span id="L346" rel="#L346">346</span>
<span id="L347" rel="#L347">347</span>
<span id="L348" rel="#L348">348</span>
<span id="L349" rel="#L349">349</span>
<span id="L350" rel="#L350">350</span>
<span id="L351" rel="#L351">351</span>
<span id="L352" rel="#L352">352</span>
<span id="L353" rel="#L353">353</span>
<span id="L354" rel="#L354">354</span>
<span id="L355" rel="#L355">355</span>
<span id="L356" rel="#L356">356</span>
<span id="L357" rel="#L357">357</span>
<span id="L358" rel="#L358">358</span>
<span id="L359" rel="#L359">359</span>
<span id="L360" rel="#L360">360</span>
<span id="L361" rel="#L361">361</span>
<span id="L362" rel="#L362">362</span>
<span id="L363" rel="#L363">363</span>
<span id="L364" rel="#L364">364</span>
<span id="L365" rel="#L365">365</span>
<span id="L366" rel="#L366">366</span>
<span id="L367" rel="#L367">367</span>
<span id="L368" rel="#L368">368</span>
<span id="L369" rel="#L369">369</span>
<span id="L370" rel="#L370">370</span>
<span id="L371" rel="#L371">371</span>
<span id="L372" rel="#L372">372</span>
<span id="L373" rel="#L373">373</span>
<span id="L374" rel="#L374">374</span>
<span id="L375" rel="#L375">375</span>
<span id="L376" rel="#L376">376</span>
<span id="L377" rel="#L377">377</span>
<span id="L378" rel="#L378">378</span>
<span id="L379" rel="#L379">379</span>
<span id="L380" rel="#L380">380</span>
<span id="L381" rel="#L381">381</span>
<span id="L382" rel="#L382">382</span>
<span id="L383" rel="#L383">383</span>
<span id="L384" rel="#L384">384</span>
<span id="L385" rel="#L385">385</span>
<span id="L386" rel="#L386">386</span>
<span id="L387" rel="#L387">387</span>
<span id="L388" rel="#L388">388</span>
<span id="L389" rel="#L389">389</span>
<span id="L390" rel="#L390">390</span>
<span id="L391" rel="#L391">391</span>
<span id="L392" rel="#L392">392</span>
<span id="L393" rel="#L393">393</span>
<span id="L394" rel="#L394">394</span>
<span id="L395" rel="#L395">395</span>
<span id="L396" rel="#L396">396</span>
<span id="L397" rel="#L397">397</span>
<span id="L398" rel="#L398">398</span>
<span id="L399" rel="#L399">399</span>
<span id="L400" rel="#L400">400</span>
<span id="L401" rel="#L401">401</span>
<span id="L402" rel="#L402">402</span>
<span id="L403" rel="#L403">403</span>
<span id="L404" rel="#L404">404</span>
<span id="L405" rel="#L405">405</span>
<span id="L406" rel="#L406">406</span>
<span id="L407" rel="#L407">407</span>
<span id="L408" rel="#L408">408</span>
<span id="L409" rel="#L409">409</span>
<span id="L410" rel="#L410">410</span>
<span id="L411" rel="#L411">411</span>
<span id="L412" rel="#L412">412</span>
<span id="L413" rel="#L413">413</span>
<span id="L414" rel="#L414">414</span>
<span id="L415" rel="#L415">415</span>
<span id="L416" rel="#L416">416</span>
<span id="L417" rel="#L417">417</span>
<span id="L418" rel="#L418">418</span>
<span id="L419" rel="#L419">419</span>
<span id="L420" rel="#L420">420</span>
<span id="L421" rel="#L421">421</span>
<span id="L422" rel="#L422">422</span>
<span id="L423" rel="#L423">423</span>
<span id="L424" rel="#L424">424</span>
<span id="L425" rel="#L425">425</span>
<span id="L426" rel="#L426">426</span>
<span id="L427" rel="#L427">427</span>
<span id="L428" rel="#L428">428</span>
<span id="L429" rel="#L429">429</span>
<span id="L430" rel="#L430">430</span>
<span id="L431" rel="#L431">431</span>
<span id="L432" rel="#L432">432</span>
<span id="L433" rel="#L433">433</span>
<span id="L434" rel="#L434">434</span>
<span id="L435" rel="#L435">435</span>
<span id="L436" rel="#L436">436</span>
<span id="L437" rel="#L437">437</span>
<span id="L438" rel="#L438">438</span>
<span id="L439" rel="#L439">439</span>
<span id="L440" rel="#L440">440</span>
<span id="L441" rel="#L441">441</span>
<span id="L442" rel="#L442">442</span>
<span id="L443" rel="#L443">443</span>
<span id="L444" rel="#L444">444</span>
<span id="L445" rel="#L445">445</span>
<span id="L446" rel="#L446">446</span>
<span id="L447" rel="#L447">447</span>
<span id="L448" rel="#L448">448</span>
<span id="L449" rel="#L449">449</span>
<span id="L450" rel="#L450">450</span>
<span id="L451" rel="#L451">451</span>
<span id="L452" rel="#L452">452</span>
<span id="L453" rel="#L453">453</span>
<span id="L454" rel="#L454">454</span>
<span id="L455" rel="#L455">455</span>
<span id="L456" rel="#L456">456</span>
<span id="L457" rel="#L457">457</span>
<span id="L458" rel="#L458">458</span>
<span id="L459" rel="#L459">459</span>
<span id="L460" rel="#L460">460</span>
<span id="L461" rel="#L461">461</span>
<span id="L462" rel="#L462">462</span>
<span id="L463" rel="#L463">463</span>
<span id="L464" rel="#L464">464</span>
<span id="L465" rel="#L465">465</span>
<span id="L466" rel="#L466">466</span>
<span id="L467" rel="#L467">467</span>
<span id="L468" rel="#L468">468</span>
<span id="L469" rel="#L469">469</span>
<span id="L470" rel="#L470">470</span>
<span id="L471" rel="#L471">471</span>
<span id="L472" rel="#L472">472</span>
<span id="L473" rel="#L473">473</span>
<span id="L474" rel="#L474">474</span>
<span id="L475" rel="#L475">475</span>
<span id="L476" rel="#L476">476</span>
<span id="L477" rel="#L477">477</span>
<span id="L478" rel="#L478">478</span>
<span id="L479" rel="#L479">479</span>
<span id="L480" rel="#L480">480</span>
<span id="L481" rel="#L481">481</span>
<span id="L482" rel="#L482">482</span>
<span id="L483" rel="#L483">483</span>
<span id="L484" rel="#L484">484</span>
<span id="L485" rel="#L485">485</span>
<span id="L486" rel="#L486">486</span>
<span id="L487" rel="#L487">487</span>
<span id="L488" rel="#L488">488</span>
<span id="L489" rel="#L489">489</span>
<span id="L490" rel="#L490">490</span>
<span id="L491" rel="#L491">491</span>
<span id="L492" rel="#L492">492</span>
<span id="L493" rel="#L493">493</span>
<span id="L494" rel="#L494">494</span>
<span id="L495" rel="#L495">495</span>
<span id="L496" rel="#L496">496</span>
<span id="L497" rel="#L497">497</span>
<span id="L498" rel="#L498">498</span>
<span id="L499" rel="#L499">499</span>
<span id="L500" rel="#L500">500</span>
<span id="L501" rel="#L501">501</span>
<span id="L502" rel="#L502">502</span>
<span id="L503" rel="#L503">503</span>
<span id="L504" rel="#L504">504</span>
<span id="L505" rel="#L505">505</span>
<span id="L506" rel="#L506">506</span>
<span id="L507" rel="#L507">507</span>
<span id="L508" rel="#L508">508</span>
<span id="L509" rel="#L509">509</span>
<span id="L510" rel="#L510">510</span>
<span id="L511" rel="#L511">511</span>
<span id="L512" rel="#L512">512</span>
<span id="L513" rel="#L513">513</span>
<span id="L514" rel="#L514">514</span>
<span id="L515" rel="#L515">515</span>
<span id="L516" rel="#L516">516</span>
<span id="L517" rel="#L517">517</span>
<span id="L518" rel="#L518">518</span>
<span id="L519" rel="#L519">519</span>
<span id="L520" rel="#L520">520</span>
<span id="L521" rel="#L521">521</span>
<span id="L522" rel="#L522">522</span>
<span id="L523" rel="#L523">523</span>
<span id="L524" rel="#L524">524</span>
<span id="L525" rel="#L525">525</span>
<span id="L526" rel="#L526">526</span>
<span id="L527" rel="#L527">527</span>
<span id="L528" rel="#L528">528</span>
<span id="L529" rel="#L529">529</span>
<span id="L530" rel="#L530">530</span>
<span id="L531" rel="#L531">531</span>
<span id="L532" rel="#L532">532</span>
<span id="L533" rel="#L533">533</span>
<span id="L534" rel="#L534">534</span>
<span id="L535" rel="#L535">535</span>
<span id="L536" rel="#L536">536</span>
<span id="L537" rel="#L537">537</span>
<span id="L538" rel="#L538">538</span>
<span id="L539" rel="#L539">539</span>
<span id="L540" rel="#L540">540</span>
<span id="L541" rel="#L541">541</span>
<span id="L542" rel="#L542">542</span>
<span id="L543" rel="#L543">543</span>
<span id="L544" rel="#L544">544</span>
<span id="L545" rel="#L545">545</span>
<span id="L546" rel="#L546">546</span>
<span id="L547" rel="#L547">547</span>
<span id="L548" rel="#L548">548</span>
<span id="L549" rel="#L549">549</span>
<span id="L550" rel="#L550">550</span>
<span id="L551" rel="#L551">551</span>
<span id="L552" rel="#L552">552</span>
<span id="L553" rel="#L553">553</span>
<span id="L554" rel="#L554">554</span>
<span id="L555" rel="#L555">555</span>
<span id="L556" rel="#L556">556</span>
<span id="L557" rel="#L557">557</span>
<span id="L558" rel="#L558">558</span>
<span id="L559" rel="#L559">559</span>
<span id="L560" rel="#L560">560</span>
<span id="L561" rel="#L561">561</span>
<span id="L562" rel="#L562">562</span>
<span id="L563" rel="#L563">563</span>
<span id="L564" rel="#L564">564</span>
<span id="L565" rel="#L565">565</span>
<span id="L566" rel="#L566">566</span>
<span id="L567" rel="#L567">567</span>
<span id="L568" rel="#L568">568</span>
<span id="L569" rel="#L569">569</span>
<span id="L570" rel="#L570">570</span>
<span id="L571" rel="#L571">571</span>
<span id="L572" rel="#L572">572</span>
<span id="L573" rel="#L573">573</span>
<span id="L574" rel="#L574">574</span>
<span id="L575" rel="#L575">575</span>
<span id="L576" rel="#L576">576</span>
<span id="L577" rel="#L577">577</span>
<span id="L578" rel="#L578">578</span>
<span id="L579" rel="#L579">579</span>
<span id="L580" rel="#L580">580</span>
<span id="L581" rel="#L581">581</span>
<span id="L582" rel="#L582">582</span>
<span id="L583" rel="#L583">583</span>
<span id="L584" rel="#L584">584</span>
<span id="L585" rel="#L585">585</span>
<span id="L586" rel="#L586">586</span>
<span id="L587" rel="#L587">587</span>
<span id="L588" rel="#L588">588</span>
<span id="L589" rel="#L589">589</span>
<span id="L590" rel="#L590">590</span>
<span id="L591" rel="#L591">591</span>
<span id="L592" rel="#L592">592</span>
<span id="L593" rel="#L593">593</span>
<span id="L594" rel="#L594">594</span>
<span id="L595" rel="#L595">595</span>
<span id="L596" rel="#L596">596</span>
<span id="L597" rel="#L597">597</span>
<span id="L598" rel="#L598">598</span>
<span id="L599" rel="#L599">599</span>
<span id="L600" rel="#L600">600</span>
<span id="L601" rel="#L601">601</span>
<span id="L602" rel="#L602">602</span>
<span id="L603" rel="#L603">603</span>
<span id="L604" rel="#L604">604</span>
<span id="L605" rel="#L605">605</span>
<span id="L606" rel="#L606">606</span>
<span id="L607" rel="#L607">607</span>
<span id="L608" rel="#L608">608</span>
<span id="L609" rel="#L609">609</span>
<span id="L610" rel="#L610">610</span>
<span id="L611" rel="#L611">611</span>
<span id="L612" rel="#L612">612</span>
<span id="L613" rel="#L613">613</span>
<span id="L614" rel="#L614">614</span>
<span id="L615" rel="#L615">615</span>
<span id="L616" rel="#L616">616</span>
<span id="L617" rel="#L617">617</span>
<span id="L618" rel="#L618">618</span>
<span id="L619" rel="#L619">619</span>
<span id="L620" rel="#L620">620</span>
<span id="L621" rel="#L621">621</span>
<span id="L622" rel="#L622">622</span>
<span id="L623" rel="#L623">623</span>
<span id="L624" rel="#L624">624</span>
<span id="L625" rel="#L625">625</span>
<span id="L626" rel="#L626">626</span>
<span id="L627" rel="#L627">627</span>
<span id="L628" rel="#L628">628</span>
<span id="L629" rel="#L629">629</span>
<span id="L630" rel="#L630">630</span>
<span id="L631" rel="#L631">631</span>
<span id="L632" rel="#L632">632</span>
<span id="L633" rel="#L633">633</span>
<span id="L634" rel="#L634">634</span>
<span id="L635" rel="#L635">635</span>
<span id="L636" rel="#L636">636</span>
<span id="L637" rel="#L637">637</span>
<span id="L638" rel="#L638">638</span>
<span id="L639" rel="#L639">639</span>
<span id="L640" rel="#L640">640</span>
<span id="L641" rel="#L641">641</span>
<span id="L642" rel="#L642">642</span>
<span id="L643" rel="#L643">643</span>
<span id="L644" rel="#L644">644</span>
<span id="L645" rel="#L645">645</span>
<span id="L646" rel="#L646">646</span>
<span id="L647" rel="#L647">647</span>
<span id="L648" rel="#L648">648</span>
<span id="L649" rel="#L649">649</span>
<span id="L650" rel="#L650">650</span>
<span id="L651" rel="#L651">651</span>
<span id="L652" rel="#L652">652</span>
<span id="L653" rel="#L653">653</span>
<span id="L654" rel="#L654">654</span>
<span id="L655" rel="#L655">655</span>
<span id="L656" rel="#L656">656</span>
<span id="L657" rel="#L657">657</span>
<span id="L658" rel="#L658">658</span>
<span id="L659" rel="#L659">659</span>
<span id="L660" rel="#L660">660</span>
<span id="L661" rel="#L661">661</span>
<span id="L662" rel="#L662">662</span>
<span id="L663" rel="#L663">663</span>
<span id="L664" rel="#L664">664</span>
<span id="L665" rel="#L665">665</span>
<span id="L666" rel="#L666">666</span>
<span id="L667" rel="#L667">667</span>
<span id="L668" rel="#L668">668</span>
<span id="L669" rel="#L669">669</span>
<span id="L670" rel="#L670">670</span>
<span id="L671" rel="#L671">671</span>
<span id="L672" rel="#L672">672</span>
<span id="L673" rel="#L673">673</span>
<span id="L674" rel="#L674">674</span>
<span id="L675" rel="#L675">675</span>
<span id="L676" rel="#L676">676</span>
<span id="L677" rel="#L677">677</span>
<span id="L678" rel="#L678">678</span>
<span id="L679" rel="#L679">679</span>
<span id="L680" rel="#L680">680</span>
<span id="L681" rel="#L681">681</span>
<span id="L682" rel="#L682">682</span>
<span id="L683" rel="#L683">683</span>
<span id="L684" rel="#L684">684</span>
<span id="L685" rel="#L685">685</span>
<span id="L686" rel="#L686">686</span>
<span id="L687" rel="#L687">687</span>
<span id="L688" rel="#L688">688</span>
<span id="L689" rel="#L689">689</span>
<span id="L690" rel="#L690">690</span>
<span id="L691" rel="#L691">691</span>
<span id="L692" rel="#L692">692</span>
<span id="L693" rel="#L693">693</span>
<span id="L694" rel="#L694">694</span>
<span id="L695" rel="#L695">695</span>
<span id="L696" rel="#L696">696</span>
<span id="L697" rel="#L697">697</span>
<span id="L698" rel="#L698">698</span>
<span id="L699" rel="#L699">699</span>
<span id="L700" rel="#L700">700</span>
<span id="L701" rel="#L701">701</span>
<span id="L702" rel="#L702">702</span>
<span id="L703" rel="#L703">703</span>
<span id="L704" rel="#L704">704</span>
<span id="L705" rel="#L705">705</span>
<span id="L706" rel="#L706">706</span>
<span id="L707" rel="#L707">707</span>
<span id="L708" rel="#L708">708</span>
<span id="L709" rel="#L709">709</span>
<span id="L710" rel="#L710">710</span>
<span id="L711" rel="#L711">711</span>
<span id="L712" rel="#L712">712</span>
<span id="L713" rel="#L713">713</span>
<span id="L714" rel="#L714">714</span>
<span id="L715" rel="#L715">715</span>
<span id="L716" rel="#L716">716</span>
<span id="L717" rel="#L717">717</span>
<span id="L718" rel="#L718">718</span>
<span id="L719" rel="#L719">719</span>
<span id="L720" rel="#L720">720</span>
<span id="L721" rel="#L721">721</span>
<span id="L722" rel="#L722">722</span>
<span id="L723" rel="#L723">723</span>
<span id="L724" rel="#L724">724</span>
<span id="L725" rel="#L725">725</span>
<span id="L726" rel="#L726">726</span>
<span id="L727" rel="#L727">727</span>
<span id="L728" rel="#L728">728</span>
<span id="L729" rel="#L729">729</span>
<span id="L730" rel="#L730">730</span>
<span id="L731" rel="#L731">731</span>
<span id="L732" rel="#L732">732</span>
<span id="L733" rel="#L733">733</span>
<span id="L734" rel="#L734">734</span>
<span id="L735" rel="#L735">735</span>
<span id="L736" rel="#L736">736</span>
<span id="L737" rel="#L737">737</span>
<span id="L738" rel="#L738">738</span>
<span id="L739" rel="#L739">739</span>
<span id="L740" rel="#L740">740</span>
<span id="L741" rel="#L741">741</span>
<span id="L742" rel="#L742">742</span>
<span id="L743" rel="#L743">743</span>
<span id="L744" rel="#L744">744</span>
<span id="L745" rel="#L745">745</span>
<span id="L746" rel="#L746">746</span>
<span id="L747" rel="#L747">747</span>
<span id="L748" rel="#L748">748</span>
<span id="L749" rel="#L749">749</span>
<span id="L750" rel="#L750">750</span>
<span id="L751" rel="#L751">751</span>
<span id="L752" rel="#L752">752</span>
<span id="L753" rel="#L753">753</span>
<span id="L754" rel="#L754">754</span>
<span id="L755" rel="#L755">755</span>
<span id="L756" rel="#L756">756</span>
<span id="L757" rel="#L757">757</span>
<span id="L758" rel="#L758">758</span>
<span id="L759" rel="#L759">759</span>
<span id="L760" rel="#L760">760</span>
<span id="L761" rel="#L761">761</span>
<span id="L762" rel="#L762">762</span>
<span id="L763" rel="#L763">763</span>
<span id="L764" rel="#L764">764</span>
<span id="L765" rel="#L765">765</span>
<span id="L766" rel="#L766">766</span>
<span id="L767" rel="#L767">767</span>
<span id="L768" rel="#L768">768</span>
<span id="L769" rel="#L769">769</span>
<span id="L770" rel="#L770">770</span>
<span id="L771" rel="#L771">771</span>
<span id="L772" rel="#L772">772</span>
<span id="L773" rel="#L773">773</span>
<span id="L774" rel="#L774">774</span>
<span id="L775" rel="#L775">775</span>
<span id="L776" rel="#L776">776</span>
<span id="L777" rel="#L777">777</span>
<span id="L778" rel="#L778">778</span>
<span id="L779" rel="#L779">779</span>
<span id="L780" rel="#L780">780</span>
<span id="L781" rel="#L781">781</span>
<span id="L782" rel="#L782">782</span>
<span id="L783" rel="#L783">783</span>
<span id="L784" rel="#L784">784</span>
<span id="L785" rel="#L785">785</span>
<span id="L786" rel="#L786">786</span>
<span id="L787" rel="#L787">787</span>
<span id="L788" rel="#L788">788</span>
<span id="L789" rel="#L789">789</span>
<span id="L790" rel="#L790">790</span>
<span id="L791" rel="#L791">791</span>
<span id="L792" rel="#L792">792</span>
<span id="L793" rel="#L793">793</span>
<span id="L794" rel="#L794">794</span>
<span id="L795" rel="#L795">795</span>
<span id="L796" rel="#L796">796</span>
<span id="L797" rel="#L797">797</span>
<span id="L798" rel="#L798">798</span>
<span id="L799" rel="#L799">799</span>
<span id="L800" rel="#L800">800</span>
<span id="L801" rel="#L801">801</span>
<span id="L802" rel="#L802">802</span>
<span id="L803" rel="#L803">803</span>
<span id="L804" rel="#L804">804</span>
<span id="L805" rel="#L805">805</span>
<span id="L806" rel="#L806">806</span>
<span id="L807" rel="#L807">807</span>
<span id="L808" rel="#L808">808</span>
<span id="L809" rel="#L809">809</span>
<span id="L810" rel="#L810">810</span>
<span id="L811" rel="#L811">811</span>
<span id="L812" rel="#L812">812</span>
<span id="L813" rel="#L813">813</span>
<span id="L814" rel="#L814">814</span>
<span id="L815" rel="#L815">815</span>
<span id="L816" rel="#L816">816</span>
<span id="L817" rel="#L817">817</span>
<span id="L818" rel="#L818">818</span>
<span id="L819" rel="#L819">819</span>
<span id="L820" rel="#L820">820</span>
<span id="L821" rel="#L821">821</span>
<span id="L822" rel="#L822">822</span>
<span id="L823" rel="#L823">823</span>
<span id="L824" rel="#L824">824</span>
<span id="L825" rel="#L825">825</span>
<span id="L826" rel="#L826">826</span>
<span id="L827" rel="#L827">827</span>
<span id="L828" rel="#L828">828</span>
<span id="L829" rel="#L829">829</span>
<span id="L830" rel="#L830">830</span>
<span id="L831" rel="#L831">831</span>
<span id="L832" rel="#L832">832</span>
<span id="L833" rel="#L833">833</span>
<span id="L834" rel="#L834">834</span>
<span id="L835" rel="#L835">835</span>
<span id="L836" rel="#L836">836</span>
<span id="L837" rel="#L837">837</span>
<span id="L838" rel="#L838">838</span>
<span id="L839" rel="#L839">839</span>
<span id="L840" rel="#L840">840</span>
<span id="L841" rel="#L841">841</span>
<span id="L842" rel="#L842">842</span>
<span id="L843" rel="#L843">843</span>
<span id="L844" rel="#L844">844</span>
<span id="L845" rel="#L845">845</span>
<span id="L846" rel="#L846">846</span>
<span id="L847" rel="#L847">847</span>
<span id="L848" rel="#L848">848</span>
<span id="L849" rel="#L849">849</span>
<span id="L850" rel="#L850">850</span>
<span id="L851" rel="#L851">851</span>
<span id="L852" rel="#L852">852</span>
<span id="L853" rel="#L853">853</span>
<span id="L854" rel="#L854">854</span>
<span id="L855" rel="#L855">855</span>
<span id="L856" rel="#L856">856</span>
<span id="L857" rel="#L857">857</span>
<span id="L858" rel="#L858">858</span>
<span id="L859" rel="#L859">859</span>
<span id="L860" rel="#L860">860</span>
<span id="L861" rel="#L861">861</span>
<span id="L862" rel="#L862">862</span>
<span id="L863" rel="#L863">863</span>
<span id="L864" rel="#L864">864</span>
<span id="L865" rel="#L865">865</span>
<span id="L866" rel="#L866">866</span>
<span id="L867" rel="#L867">867</span>
<span id="L868" rel="#L868">868</span>
<span id="L869" rel="#L869">869</span>
<span id="L870" rel="#L870">870</span>
<span id="L871" rel="#L871">871</span>
<span id="L872" rel="#L872">872</span>
<span id="L873" rel="#L873">873</span>
<span id="L874" rel="#L874">874</span>
<span id="L875" rel="#L875">875</span>
<span id="L876" rel="#L876">876</span>
<span id="L877" rel="#L877">877</span>
<span id="L878" rel="#L878">878</span>
<span id="L879" rel="#L879">879</span>
<span id="L880" rel="#L880">880</span>
<span id="L881" rel="#L881">881</span>
<span id="L882" rel="#L882">882</span>
<span id="L883" rel="#L883">883</span>
<span id="L884" rel="#L884">884</span>
<span id="L885" rel="#L885">885</span>
<span id="L886" rel="#L886">886</span>
<span id="L887" rel="#L887">887</span>
<span id="L888" rel="#L888">888</span>
<span id="L889" rel="#L889">889</span>
<span id="L890" rel="#L890">890</span>
<span id="L891" rel="#L891">891</span>
<span id="L892" rel="#L892">892</span>
<span id="L893" rel="#L893">893</span>
<span id="L894" rel="#L894">894</span>
<span id="L895" rel="#L895">895</span>
<span id="L896" rel="#L896">896</span>
<span id="L897" rel="#L897">897</span>
<span id="L898" rel="#L898">898</span>
<span id="L899" rel="#L899">899</span>
<span id="L900" rel="#L900">900</span>
<span id="L901" rel="#L901">901</span>
<span id="L902" rel="#L902">902</span>
<span id="L903" rel="#L903">903</span>
<span id="L904" rel="#L904">904</span>
<span id="L905" rel="#L905">905</span>
<span id="L906" rel="#L906">906</span>
<span id="L907" rel="#L907">907</span>
<span id="L908" rel="#L908">908</span>
<span id="L909" rel="#L909">909</span>
<span id="L910" rel="#L910">910</span>
<span id="L911" rel="#L911">911</span>
<span id="L912" rel="#L912">912</span>
<span id="L913" rel="#L913">913</span>
<span id="L914" rel="#L914">914</span>
<span id="L915" rel="#L915">915</span>
<span id="L916" rel="#L916">916</span>
<span id="L917" rel="#L917">917</span>
<span id="L918" rel="#L918">918</span>
<span id="L919" rel="#L919">919</span>
<span id="L920" rel="#L920">920</span>
<span id="L921" rel="#L921">921</span>
<span id="L922" rel="#L922">922</span>
<span id="L923" rel="#L923">923</span>
<span id="L924" rel="#L924">924</span>
<span id="L925" rel="#L925">925</span>
<span id="L926" rel="#L926">926</span>
<span id="L927" rel="#L927">927</span>
<span id="L928" rel="#L928">928</span>
<span id="L929" rel="#L929">929</span>
<span id="L930" rel="#L930">930</span>
<span id="L931" rel="#L931">931</span>
<span id="L932" rel="#L932">932</span>
<span id="L933" rel="#L933">933</span>
<span id="L934" rel="#L934">934</span>
<span id="L935" rel="#L935">935</span>
<span id="L936" rel="#L936">936</span>
<span id="L937" rel="#L937">937</span>
<span id="L938" rel="#L938">938</span>
<span id="L939" rel="#L939">939</span>
<span id="L940" rel="#L940">940</span>
<span id="L941" rel="#L941">941</span>
<span id="L942" rel="#L942">942</span>
<span id="L943" rel="#L943">943</span>
<span id="L944" rel="#L944">944</span>
<span id="L945" rel="#L945">945</span>
<span id="L946" rel="#L946">946</span>
<span id="L947" rel="#L947">947</span>
<span id="L948" rel="#L948">948</span>
<span id="L949" rel="#L949">949</span>
<span id="L950" rel="#L950">950</span>
<span id="L951" rel="#L951">951</span>
<span id="L952" rel="#L952">952</span>
<span id="L953" rel="#L953">953</span>
<span id="L954" rel="#L954">954</span>
<span id="L955" rel="#L955">955</span>
<span id="L956" rel="#L956">956</span>
<span id="L957" rel="#L957">957</span>
<span id="L958" rel="#L958">958</span>
<span id="L959" rel="#L959">959</span>
<span id="L960" rel="#L960">960</span>
<span id="L961" rel="#L961">961</span>
<span id="L962" rel="#L962">962</span>
<span id="L963" rel="#L963">963</span>
<span id="L964" rel="#L964">964</span>
<span id="L965" rel="#L965">965</span>
<span id="L966" rel="#L966">966</span>
<span id="L967" rel="#L967">967</span>
<span id="L968" rel="#L968">968</span>
<span id="L969" rel="#L969">969</span>
<span id="L970" rel="#L970">970</span>
<span id="L971" rel="#L971">971</span>
<span id="L972" rel="#L972">972</span>
<span id="L973" rel="#L973">973</span>
<span id="L974" rel="#L974">974</span>
<span id="L975" rel="#L975">975</span>
<span id="L976" rel="#L976">976</span>
<span id="L977" rel="#L977">977</span>
<span id="L978" rel="#L978">978</span>
<span id="L979" rel="#L979">979</span>
<span id="L980" rel="#L980">980</span>
<span id="L981" rel="#L981">981</span>
<span id="L982" rel="#L982">982</span>
<span id="L983" rel="#L983">983</span>
<span id="L984" rel="#L984">984</span>
<span id="L985" rel="#L985">985</span>
<span id="L986" rel="#L986">986</span>
<span id="L987" rel="#L987">987</span>
<span id="L988" rel="#L988">988</span>
<span id="L989" rel="#L989">989</span>
<span id="L990" rel="#L990">990</span>
<span id="L991" rel="#L991">991</span>
<span id="L992" rel="#L992">992</span>
<span id="L993" rel="#L993">993</span>
<span id="L994" rel="#L994">994</span>
<span id="L995" rel="#L995">995</span>
<span id="L996" rel="#L996">996</span>
<span id="L997" rel="#L997">997</span>
<span id="L998" rel="#L998">998</span>
<span id="L999" rel="#L999">999</span>
<span id="L1000" rel="#L1000">1000</span>
<span id="L1001" rel="#L1001">1001</span>
<span id="L1002" rel="#L1002">1002</span>
<span id="L1003" rel="#L1003">1003</span>
<span id="L1004" rel="#L1004">1004</span>
<span id="L1005" rel="#L1005">1005</span>
<span id="L1006" rel="#L1006">1006</span>
<span id="L1007" rel="#L1007">1007</span>
<span id="L1008" rel="#L1008">1008</span>
<span id="L1009" rel="#L1009">1009</span>
<span id="L1010" rel="#L1010">1010</span>
<span id="L1011" rel="#L1011">1011</span>
<span id="L1012" rel="#L1012">1012</span>
<span id="L1013" rel="#L1013">1013</span>
<span id="L1014" rel="#L1014">1014</span>
<span id="L1015" rel="#L1015">1015</span>
<span id="L1016" rel="#L1016">1016</span>
<span id="L1017" rel="#L1017">1017</span>
<span id="L1018" rel="#L1018">1018</span>
<span id="L1019" rel="#L1019">1019</span>
<span id="L1020" rel="#L1020">1020</span>
<span id="L1021" rel="#L1021">1021</span>
<span id="L1022" rel="#L1022">1022</span>
<span id="L1023" rel="#L1023">1023</span>
<span id="L1024" rel="#L1024">1024</span>
<span id="L1025" rel="#L1025">1025</span>
<span id="L1026" rel="#L1026">1026</span>
<span id="L1027" rel="#L1027">1027</span>
<span id="L1028" rel="#L1028">1028</span>
<span id="L1029" rel="#L1029">1029</span>
<span id="L1030" rel="#L1030">1030</span>
<span id="L1031" rel="#L1031">1031</span>
<span id="L1032" rel="#L1032">1032</span>
<span id="L1033" rel="#L1033">1033</span>
<span id="L1034" rel="#L1034">1034</span>
<span id="L1035" rel="#L1035">1035</span>
<span id="L1036" rel="#L1036">1036</span>
<span id="L1037" rel="#L1037">1037</span>
<span id="L1038" rel="#L1038">1038</span>
<span id="L1039" rel="#L1039">1039</span>
<span id="L1040" rel="#L1040">1040</span>
<span id="L1041" rel="#L1041">1041</span>
<span id="L1042" rel="#L1042">1042</span>
<span id="L1043" rel="#L1043">1043</span>
<span id="L1044" rel="#L1044">1044</span>
<span id="L1045" rel="#L1045">1045</span>
<span id="L1046" rel="#L1046">1046</span>
<span id="L1047" rel="#L1047">1047</span>
<span id="L1048" rel="#L1048">1048</span>
<span id="L1049" rel="#L1049">1049</span>
<span id="L1050" rel="#L1050">1050</span>
<span id="L1051" rel="#L1051">1051</span>
<span id="L1052" rel="#L1052">1052</span>
<span id="L1053" rel="#L1053">1053</span>
<span id="L1054" rel="#L1054">1054</span>
<span id="L1055" rel="#L1055">1055</span>
<span id="L1056" rel="#L1056">1056</span>
<span id="L1057" rel="#L1057">1057</span>
<span id="L1058" rel="#L1058">1058</span>
<span id="L1059" rel="#L1059">1059</span>
<span id="L1060" rel="#L1060">1060</span>
<span id="L1061" rel="#L1061">1061</span>
<span id="L1062" rel="#L1062">1062</span>
<span id="L1063" rel="#L1063">1063</span>
<span id="L1064" rel="#L1064">1064</span>
<span id="L1065" rel="#L1065">1065</span>
<span id="L1066" rel="#L1066">1066</span>
<span id="L1067" rel="#L1067">1067</span>
<span id="L1068" rel="#L1068">1068</span>
<span id="L1069" rel="#L1069">1069</span>
<span id="L1070" rel="#L1070">1070</span>
<span id="L1071" rel="#L1071">1071</span>
<span id="L1072" rel="#L1072">1072</span>
<span id="L1073" rel="#L1073">1073</span>
<span id="L1074" rel="#L1074">1074</span>
<span id="L1075" rel="#L1075">1075</span>
<span id="L1076" rel="#L1076">1076</span>
<span id="L1077" rel="#L1077">1077</span>
<span id="L1078" rel="#L1078">1078</span>
<span id="L1079" rel="#L1079">1079</span>
<span id="L1080" rel="#L1080">1080</span>
<span id="L1081" rel="#L1081">1081</span>
<span id="L1082" rel="#L1082">1082</span>
<span id="L1083" rel="#L1083">1083</span>
<span id="L1084" rel="#L1084">1084</span>
<span id="L1085" rel="#L1085">1085</span>
<span id="L1086" rel="#L1086">1086</span>
<span id="L1087" rel="#L1087">1087</span>
<span id="L1088" rel="#L1088">1088</span>
<span id="L1089" rel="#L1089">1089</span>
<span id="L1090" rel="#L1090">1090</span>
<span id="L1091" rel="#L1091">1091</span>
<span id="L1092" rel="#L1092">1092</span>
<span id="L1093" rel="#L1093">1093</span>
<span id="L1094" rel="#L1094">1094</span>
<span id="L1095" rel="#L1095">1095</span>
<span id="L1096" rel="#L1096">1096</span>
<span id="L1097" rel="#L1097">1097</span>
<span id="L1098" rel="#L1098">1098</span>
<span id="L1099" rel="#L1099">1099</span>
<span id="L1100" rel="#L1100">1100</span>
<span id="L1101" rel="#L1101">1101</span>
<span id="L1102" rel="#L1102">1102</span>
<span id="L1103" rel="#L1103">1103</span>
<span id="L1104" rel="#L1104">1104</span>
<span id="L1105" rel="#L1105">1105</span>
<span id="L1106" rel="#L1106">1106</span>
<span id="L1107" rel="#L1107">1107</span>
<span id="L1108" rel="#L1108">1108</span>
<span id="L1109" rel="#L1109">1109</span>
<span id="L1110" rel="#L1110">1110</span>
<span id="L1111" rel="#L1111">1111</span>
<span id="L1112" rel="#L1112">1112</span>
<span id="L1113" rel="#L1113">1113</span>
<span id="L1114" rel="#L1114">1114</span>
<span id="L1115" rel="#L1115">1115</span>
<span id="L1116" rel="#L1116">1116</span>
<span id="L1117" rel="#L1117">1117</span>
<span id="L1118" rel="#L1118">1118</span>
<span id="L1119" rel="#L1119">1119</span>
<span id="L1120" rel="#L1120">1120</span>
<span id="L1121" rel="#L1121">1121</span>
<span id="L1122" rel="#L1122">1122</span>
<span id="L1123" rel="#L1123">1123</span>
<span id="L1124" rel="#L1124">1124</span>
<span id="L1125" rel="#L1125">1125</span>
<span id="L1126" rel="#L1126">1126</span>
<span id="L1127" rel="#L1127">1127</span>
<span id="L1128" rel="#L1128">1128</span>
<span id="L1129" rel="#L1129">1129</span>
<span id="L1130" rel="#L1130">1130</span>
<span id="L1131" rel="#L1131">1131</span>
<span id="L1132" rel="#L1132">1132</span>
<span id="L1133" rel="#L1133">1133</span>
<span id="L1134" rel="#L1134">1134</span>
<span id="L1135" rel="#L1135">1135</span>
<span id="L1136" rel="#L1136">1136</span>
<span id="L1137" rel="#L1137">1137</span>
<span id="L1138" rel="#L1138">1138</span>
<span id="L1139" rel="#L1139">1139</span>
<span id="L1140" rel="#L1140">1140</span>
<span id="L1141" rel="#L1141">1141</span>
<span id="L1142" rel="#L1142">1142</span>
<span id="L1143" rel="#L1143">1143</span>
<span id="L1144" rel="#L1144">1144</span>
<span id="L1145" rel="#L1145">1145</span>
<span id="L1146" rel="#L1146">1146</span>
<span id="L1147" rel="#L1147">1147</span>
<span id="L1148" rel="#L1148">1148</span>
<span id="L1149" rel="#L1149">1149</span>
<span id="L1150" rel="#L1150">1150</span>
<span id="L1151" rel="#L1151">1151</span>
<span id="L1152" rel="#L1152">1152</span>
<span id="L1153" rel="#L1153">1153</span>
<span id="L1154" rel="#L1154">1154</span>
<span id="L1155" rel="#L1155">1155</span>
<span id="L1156" rel="#L1156">1156</span>
<span id="L1157" rel="#L1157">1157</span>
<span id="L1158" rel="#L1158">1158</span>
<span id="L1159" rel="#L1159">1159</span>
<span id="L1160" rel="#L1160">1160</span>
<span id="L1161" rel="#L1161">1161</span>
<span id="L1162" rel="#L1162">1162</span>
<span id="L1163" rel="#L1163">1163</span>
<span id="L1164" rel="#L1164">1164</span>
<span id="L1165" rel="#L1165">1165</span>
<span id="L1166" rel="#L1166">1166</span>
<span id="L1167" rel="#L1167">1167</span>
<span id="L1168" rel="#L1168">1168</span>
<span id="L1169" rel="#L1169">1169</span>
<span id="L1170" rel="#L1170">1170</span>
<span id="L1171" rel="#L1171">1171</span>
<span id="L1172" rel="#L1172">1172</span>
<span id="L1173" rel="#L1173">1173</span>
<span id="L1174" rel="#L1174">1174</span>
<span id="L1175" rel="#L1175">1175</span>
<span id="L1176" rel="#L1176">1176</span>
<span id="L1177" rel="#L1177">1177</span>
<span id="L1178" rel="#L1178">1178</span>
<span id="L1179" rel="#L1179">1179</span>
<span id="L1180" rel="#L1180">1180</span>
<span id="L1181" rel="#L1181">1181</span>
<span id="L1182" rel="#L1182">1182</span>
<span id="L1183" rel="#L1183">1183</span>
<span id="L1184" rel="#L1184">1184</span>
<span id="L1185" rel="#L1185">1185</span>
<span id="L1186" rel="#L1186">1186</span>
<span id="L1187" rel="#L1187">1187</span>
<span id="L1188" rel="#L1188">1188</span>
<span id="L1189" rel="#L1189">1189</span>
<span id="L1190" rel="#L1190">1190</span>
<span id="L1191" rel="#L1191">1191</span>
<span id="L1192" rel="#L1192">1192</span>
<span id="L1193" rel="#L1193">1193</span>
<span id="L1194" rel="#L1194">1194</span>
<span id="L1195" rel="#L1195">1195</span>
<span id="L1196" rel="#L1196">1196</span>
<span id="L1197" rel="#L1197">1197</span>
<span id="L1198" rel="#L1198">1198</span>
<span id="L1199" rel="#L1199">1199</span>
<span id="L1200" rel="#L1200">1200</span>
<span id="L1201" rel="#L1201">1201</span>
<span id="L1202" rel="#L1202">1202</span>
<span id="L1203" rel="#L1203">1203</span>
<span id="L1204" rel="#L1204">1204</span>
<span id="L1205" rel="#L1205">1205</span>
<span id="L1206" rel="#L1206">1206</span>
<span id="L1207" rel="#L1207">1207</span>
<span id="L1208" rel="#L1208">1208</span>
<span id="L1209" rel="#L1209">1209</span>
<span id="L1210" rel="#L1210">1210</span>
<span id="L1211" rel="#L1211">1211</span>
<span id="L1212" rel="#L1212">1212</span>
<span id="L1213" rel="#L1213">1213</span>
<span id="L1214" rel="#L1214">1214</span>
<span id="L1215" rel="#L1215">1215</span>
<span id="L1216" rel="#L1216">1216</span>

           </td>
           <td class="blob-line-code"><div class="code-body highlight"><pre><div class='line' id='LC1'><span class="cm">/*</span></div><div class='line' id='LC2'><span class="cm"> Copyright (C) 2011 J. Coliz &lt;maniacbug@ymail.com&gt;</span></div><div class='line' id='LC3'><br></div><div class='line' id='LC4'><span class="cm"> This program is free software; you can redistribute it and/or</span></div><div class='line' id='LC5'><span class="cm"> modify it under the terms of the GNU General Public License</span></div><div class='line' id='LC6'><span class="cm"> version 2 as published by the Free Software Foundation.</span></div><div class='line' id='LC7'><span class="cm"> */</span></div><div class='line' id='LC8'><br></div><div class='line' id='LC9'><span class="cm">/**</span></div><div class='line' id='LC10'><span class="cm"> * @file RF24.h</span></div><div class='line' id='LC11'><span class="cm"> *</span></div><div class='line' id='LC12'><span class="cm"> * Class declaration for RF24 and helper enums</span></div><div class='line' id='LC13'><span class="cm"> */</span></div><div class='line' id='LC14'><br></div><div class='line' id='LC15'><span class="cp">#ifndef __RF24_H__</span></div><div class='line' id='LC16'><span class="cp">#define __RF24_H__</span></div><div class='line' id='LC17'><br></div><div class='line' id='LC18'><span class="cp">#include &lt;RF24_config.h&gt;</span></div><div class='line' id='LC19'><br></div><div class='line' id='LC20'><span class="cm">/**</span></div><div class='line' id='LC21'><span class="cm"> * Power Amplifier level.</span></div><div class='line' id='LC22'><span class="cm"> *</span></div><div class='line' id='LC23'><span class="cm"> * For use with setPALevel()</span></div><div class='line' id='LC24'><span class="cm"> */</span></div><div class='line' id='LC25'><span class="k">typedef</span> <span class="k">enum</span> <span class="p">{</span> <span class="n">RF24_PA_MIN</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span><span class="n">RF24_PA_LOW</span><span class="p">,</span> <span class="n">RF24_PA_HIGH</span><span class="p">,</span> <span class="n">RF24_PA_MAX</span><span class="p">,</span> <span class="n">RF24_PA_ERROR</span> <span class="p">}</span> <span class="n">rf24_pa_dbm_e</span> <span class="p">;</span></div><div class='line' id='LC26'><br></div><div class='line' id='LC27'><span class="cm">/**</span></div><div class='line' id='LC28'><span class="cm"> * Data rate.  How fast data moves through the air.</span></div><div class='line' id='LC29'><span class="cm"> *</span></div><div class='line' id='LC30'><span class="cm"> * For use with setDataRate()</span></div><div class='line' id='LC31'><span class="cm"> */</span></div><div class='line' id='LC32'><span class="k">typedef</span> <span class="k">enum</span> <span class="p">{</span> <span class="n">RF24_1MBPS</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">RF24_2MBPS</span><span class="p">,</span> <span class="n">RF24_250KBPS</span> <span class="p">}</span> <span class="n">rf24_datarate_e</span><span class="p">;</span></div><div class='line' id='LC33'><br></div><div class='line' id='LC34'><span class="cm">/**</span></div><div class='line' id='LC35'><span class="cm"> * CRC Length.  How big (if any) of a CRC is included.</span></div><div class='line' id='LC36'><span class="cm"> *</span></div><div class='line' id='LC37'><span class="cm"> * For use with setCRCLength()</span></div><div class='line' id='LC38'><span class="cm"> */</span></div><div class='line' id='LC39'><span class="k">typedef</span> <span class="k">enum</span> <span class="p">{</span> <span class="n">RF24_CRC_DISABLED</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">RF24_CRC_8</span><span class="p">,</span> <span class="n">RF24_CRC_16</span> <span class="p">}</span> <span class="n">rf24_crclength_e</span><span class="p">;</span></div><div class='line' id='LC40'><br></div><div class='line' id='LC41'><span class="cm">/**</span></div><div class='line' id='LC42'><span class="cm"> * Driver for nRF24L01(+) 2.4GHz Wireless Transceiver</span></div><div class='line' id='LC43'><span class="cm"> */</span></div><div class='line' id='LC44'><br></div><div class='line' id='LC45'><span class="k">class</span> <span class="nc">RF24</span></div><div class='line' id='LC46'><span class="p">{</span></div><div class='line' id='LC47'><span class="k">private</span><span class="o">:</span></div><div class='line' id='LC48'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">ce_pin</span><span class="p">;</span> <span class="cm">/**&lt; &quot;Chip Enable&quot; pin, activates the RX or TX role */</span></div><div class='line' id='LC49'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">csn_pin</span><span class="p">;</span> <span class="cm">/**&lt; SPI Chip select */</span></div><div class='line' id='LC50'>&nbsp;&nbsp;</div><div class='line' id='LC51'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="n">p_variant</span><span class="p">;</span> <span class="cm">/* False for RF24L01 and true for RF24L01P */</span></div><div class='line' id='LC52'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">payload_size</span><span class="p">;</span> <span class="cm">/**&lt; Fixed size of payloads */</span></div><div class='line' id='LC53'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="n">dynamic_payloads_enabled</span><span class="p">;</span> <span class="cm">/**&lt; Whether dynamic payloads are enabled. */</span></div><div class='line' id='LC54'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">pipe0_reading_address</span><span class="p">[</span><span class="mi">5</span><span class="p">];</span> <span class="cm">/**&lt; Last address set on pipe 0 for reading. */</span></div><div class='line' id='LC55'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">addr_width</span><span class="p">;</span></div><div class='line' id='LC56'>&nbsp;&nbsp;</div><div class='line' id='LC57'><br></div><div class='line' id='LC58'><span class="k">public</span><span class="o">:</span></div><div class='line' id='LC59'><br></div><div class='line' id='LC60'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC61'><span class="cm">   * @name Primary public interface</span></div><div class='line' id='LC62'><span class="cm">   *</span></div><div class='line' id='LC63'><span class="cm">   *  These are the main methods you need to operate the chip</span></div><div class='line' id='LC64'><span class="cm">   */</span></div><div class='line' id='LC65'>&nbsp;&nbsp;<span class="cm">/**@{*/</span></div><div class='line' id='LC66'><br></div><div class='line' id='LC67'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC68'><span class="cm">   * Constructor</span></div><div class='line' id='LC69'><span class="cm">   *</span></div><div class='line' id='LC70'><span class="cm">   * Creates a new instance of this driver.  Before using, you create an instance</span></div><div class='line' id='LC71'><span class="cm">   * and send in the unique pins that this chip is connected to.</span></div><div class='line' id='LC72'><span class="cm">   *</span></div><div class='line' id='LC73'><span class="cm">   * @param _cepin The pin attached to Chip Enable on the RF module</span></div><div class='line' id='LC74'><span class="cm">   * @param _cspin The pin attached to Chip Select</span></div><div class='line' id='LC75'><span class="cm">   */</span></div><div class='line' id='LC76'>&nbsp;&nbsp;<span class="n">RF24</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">_cepin</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">_cspin</span><span class="p">);</span></div><div class='line' id='LC77'><br></div><div class='line' id='LC78'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC79'><span class="cm">   * Begin operation of the chip</span></div><div class='line' id='LC80'><span class="cm">   *</span></div><div class='line' id='LC81'><span class="cm">   * Call this in setup(), before calling any other methods.</span></div><div class='line' id='LC82'><span class="cm">   *</span></div><div class='line' id='LC83'><span class="cm">   * @note Optimization: The radio is partially configured in PTX mode</span></div><div class='line' id='LC84'><span class="cm">   * when begin is called to make the transition to PTX mode simpler.</span></div><div class='line' id='LC85'><span class="cm">   */</span></div><div class='line' id='LC86'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">begin</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC87'><br></div><div class='line' id='LC88'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC89'><span class="cm">   * Start listening on the pipes opened for reading.</span></div><div class='line' id='LC90'><span class="cm">   *</span></div><div class='line' id='LC91'><span class="cm">   * Be sure to call openReadingPipe() first.  Do not call write() while</span></div><div class='line' id='LC92'><span class="cm">   * in this mode, without first calling stopListening().  Call</span></div><div class='line' id='LC93'><span class="cm">   * isAvailable() to check for incoming traffic, and read() to get it.</span></div><div class='line' id='LC94'><span class="cm">   */</span></div><div class='line' id='LC95'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">startListening</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC96'><br></div><div class='line' id='LC97'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC98'><span class="cm">   * Stop listening for incoming messages</span></div><div class='line' id='LC99'><span class="cm">   *</span></div><div class='line' id='LC100'><span class="cm">   * Do this before calling write().</span></div><div class='line' id='LC101'><span class="cm">   *</span></div><div class='line' id='LC102'><span class="cm">   * @note Optimization: The radio will be taken out of PRX mode as soon</span></div><div class='line' id='LC103'><span class="cm">   * as listening is stopped. Enables quicker and simpler engaging of</span></div><div class='line' id='LC104'><span class="cm">   * primary transmitter (PTX) mode.</span></div><div class='line' id='LC105'><span class="cm">   */</span></div><div class='line' id='LC106'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">stopListening</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC107'><br></div><div class='line' id='LC108'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC109'><span class="cm">   * Test whether there are bytes available to be read</span></div><div class='line' id='LC110'><span class="cm">   *</span></div><div class='line' id='LC111'><span class="cm">   * @note Optimization: The available functino now checks the FIFO</span></div><div class='line' id='LC112'><span class="cm">   * buffers directly for data instead of relying of interrupt flags.</span></div><div class='line' id='LC113'><span class="cm">   *</span></div><div class='line' id='LC114'><span class="cm">   * @note Interrupt flags will not be cleared until a payload is</span></div><div class='line' id='LC115'><span class="cm">   * actually read from the FIFO</span></div><div class='line' id='LC116'><span class="cm">   *</span></div><div class='line' id='LC117'><span class="cm">   * @see txStandBy()</span></div><div class='line' id='LC118'><span class="cm">   * @see startWrite()</span></div><div class='line' id='LC119'><span class="cm">   * @see write()</span></div><div class='line' id='LC120'><span class="cm">   * @see writeFast()</span></div><div class='line' id='LC121'><span class="cm">   *</span></div><div class='line' id='LC122'><span class="cm">   * @return True if there is a payload available, false if none is</span></div><div class='line' id='LC123'><span class="cm">   */</span></div><div class='line' id='LC124'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">available</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC125'><br></div><div class='line' id='LC126'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC127'><span class="cm">   * Read the payload</span></div><div class='line' id='LC128'><span class="cm">   *</span></div><div class='line' id='LC129'><span class="cm">   * The size of data read is the fixed payload size, see getPayloadSize()</span></div><div class='line' id='LC130'><span class="cm">   *</span></div><div class='line' id='LC131'><span class="cm">   * @note I specifically chose &#39;void*&#39; as a data type to make it easier</span></div><div class='line' id='LC132'><span class="cm">   * for beginners to use.  No casting needed.</span></div><div class='line' id='LC133'><span class="cm">   *</span></div><div class='line' id='LC134'><span class="cm">   * @note Optimization: No longer boolean. Use available to</span></div><div class='line' id='LC135'><span class="cm">   * determine if packets are available. Interrupt flags are now cleared</span></div><div class='line' id='LC136'><span class="cm">   * during reads instead of when calling available().</span></div><div class='line' id='LC137'><span class="cm">   *</span></div><div class='line' id='LC138'><span class="cm">   * @param buf Pointer to a buffer where the data should be written</span></div><div class='line' id='LC139'><span class="cm">   * @param len Maximum number of bytes to read into the buffer</span></div><div class='line' id='LC140'><span class="cm">   * @return No return value. Use available().</span></div><div class='line' id='LC141'><span class="cm">   */</span></div><div class='line' id='LC142'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">read</span><span class="p">(</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">);</span></div><div class='line' id='LC143'><br></div><div class='line' id='LC144'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC145'><span class="cm">   * @note Optimization: Improved performance slightly</span></div><div class='line' id='LC146'><span class="cm">   * Write to the open writing pipe</span></div><div class='line' id='LC147'><span class="cm">   *</span></div><div class='line' id='LC148'><span class="cm">   * Be sure to call openWritingPipe() first to set the destination</span></div><div class='line' id='LC149'><span class="cm">   * of where to write to.</span></div><div class='line' id='LC150'><span class="cm">   *</span></div><div class='line' id='LC151'><span class="cm">   * This blocks until the message is successfully acknowledged by</span></div><div class='line' id='LC152'><span class="cm">   * the receiver or the timeout/retransmit maxima are reached.  In</span></div><div class='line' id='LC153'><span class="cm">   * the current configuration, the max delay here is 60ms.</span></div><div class='line' id='LC154'><span class="cm">   *</span></div><div class='line' id='LC155'><span class="cm">   * The maximum size of data written is the fixed payload size, see</span></div><div class='line' id='LC156'><span class="cm">   * getPayloadSize().  However, you can write less, and the remainder</span></div><div class='line' id='LC157'><span class="cm">   * will just be filled with zeroes.</span></div><div class='line' id='LC158'><span class="cm">   *</span></div><div class='line' id='LC159'><span class="cm">   * TX/RX/RT interrupt flags will be cleared every time write is called</span></div><div class='line' id='LC160'><span class="cm">   *</span></div><div class='line' id='LC161'><span class="cm">   * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC162'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC163'><span class="cm">   * @return True if the payload was delivered successfully false if not</span></div><div class='line' id='LC164'><span class="cm">   */</span></div><div class='line' id='LC165'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">write</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">);</span></div><div class='line' id='LC166'><br></div><div class='line' id='LC167'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC168'><span class="cm">   * New: Open a pipe for writing</span></div><div class='line' id='LC169'><span class="cm">   *</span></div><div class='line' id='LC170'><span class="cm">   * Only one pipe can be open at once, but you can change the pipe</span></div><div class='line' id='LC171'><span class="cm">   * you&#39;ll write to. Call stopListening() first.</span></div><div class='line' id='LC172'><span class="cm">   *</span></div><div class='line' id='LC173'><span class="cm">   * Addresses are assigned via a byte array, default is 5 byte address length</span></div><div class='line' id='LC174'><span class="cm">   *</span></div><div class='line' id='LC175'><span class="cm">   * Usage is exactly the same as before, except for declaring the array</span></div><div class='line' id='LC176'><span class="cm">   *</span></div><div class='line' id='LC177'><span class="cm">   * @code</span></div><div class='line' id='LC178'><span class="cm">   *   uint8_t addresses[][6] = {&quot;1Node&quot;,&quot;2Node&quot;};</span></div><div class='line' id='LC179'><span class="cm">   *   openWritingPipe(addresses[0]);</span></div><div class='line' id='LC180'><span class="cm">   * @endcode</span></div><div class='line' id='LC181'><span class="cm">   * @see setAddressWidth</span></div><div class='line' id='LC182'><span class="cm">   *</span></div><div class='line' id='LC183'><span class="cm">   * @param address The address of the pipe to open. Coordinate these pipe</span></div><div class='line' id='LC184'><span class="cm">   * addresses amongst nodes on the network.</span></div><div class='line' id='LC185'><span class="cm">   */</span></div><div class='line' id='LC186'><br></div><div class='line' id='LC187'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">openWritingPipe</span><span class="p">(</span><span class="k">const</span> <span class="kt">uint8_t</span> <span class="o">*</span><span class="n">address</span><span class="p">);</span></div><div class='line' id='LC188'><br></div><div class='line' id='LC189'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC190'><span class="cm">   * Open a pipe for reading</span></div><div class='line' id='LC191'><span class="cm">   *</span></div><div class='line' id='LC192'><span class="cm">   * Up to 6 pipes can be open for reading at once.  Open all the</span></div><div class='line' id='LC193'><span class="cm">   * reading pipes, and then call startListening().</span></div><div class='line' id='LC194'><span class="cm">   *</span></div><div class='line' id='LC195'><span class="cm">   * @see openWritingPipe</span></div><div class='line' id='LC196'><span class="cm">   * @see setAddressWidth</span></div><div class='line' id='LC197'><span class="cm">   *</span></div><div class='line' id='LC198'><span class="cm">   * @warning Pipes 1-5 should share the same address, except the first byte.</span></div><div class='line' id='LC199'><span class="cm">   * Only the first byte in the array should be unique, e.g.</span></div><div class='line' id='LC200'><span class="cm">   * @code</span></div><div class='line' id='LC201'><span class="cm">   *   uint8_t addresses[][6] = {&quot;1Node&quot;,&quot;2Node&quot;};</span></div><div class='line' id='LC202'><span class="cm">   *   openReadingPipe(1,addresses[0]);</span></div><div class='line' id='LC203'><span class="cm">   *   openReadingPipe(2,addresses[1]);</span></div><div class='line' id='LC204'><span class="cm">   * @endcode</span></div><div class='line' id='LC205'><span class="cm">   *</span></div><div class='line' id='LC206'><span class="cm">   * @warning Pipe 0 is also used by the writing pipe.  So if you open</span></div><div class='line' id='LC207'><span class="cm">   * pipe 0 for reading, and then startListening(), it will overwrite the</span></div><div class='line' id='LC208'><span class="cm">   * writing pipe.  Ergo, do an openWritingPipe() again before write().</span></div><div class='line' id='LC209'><span class="cm">   *</span></div><div class='line' id='LC210'><span class="cm">   * @param number Which pipe# to open, 0-5.</span></div><div class='line' id='LC211'><span class="cm">   * @param address The 24, 32 or 40 bit address of the pipe to open.</span></div><div class='line' id='LC212'><span class="cm">   */</span></div><div class='line' id='LC213'><br></div><div class='line' id='LC214'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">openReadingPipe</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">number</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="o">*</span><span class="n">address</span><span class="p">);</span></div><div class='line' id='LC215'><br></div><div class='line' id='LC216'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC217'><span class="cm">   * Close a pipe after it has been previously opened.</span></div><div class='line' id='LC218'><span class="cm">   * Can be safely called without having previously opened a pipe.</span></div><div class='line' id='LC219'><span class="cm">   * @param pipe Which pipe # to close, 0-5.</span></div><div class='line' id='LC220'><span class="cm">   */</span></div><div class='line' id='LC221'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">closeReadingPipe</span><span class="p">(</span> <span class="kt">uint8_t</span> <span class="n">pipe</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC222'><br></div><div class='line' id='LC223'>&nbsp;&nbsp;<span class="cm">/**@}*/</span></div><div class='line' id='LC224'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC225'><span class="cm">   * @name Advanced Operation</span></div><div class='line' id='LC226'><span class="cm">   *</span></div><div class='line' id='LC227'><span class="cm">   *  Methods you can use to drive the chip in more advanced ways</span></div><div class='line' id='LC228'><span class="cm">   */</span></div><div class='line' id='LC229'>&nbsp;&nbsp;<span class="cm">/**@{*/</span></div><div class='line' id='LC230'><br></div><div class='line' id='LC231'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC232'><span class="cm">   * Print a giant block of debugging information to stdout</span></div><div class='line' id='LC233'><span class="cm">   *</span></div><div class='line' id='LC234'><span class="cm">   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h</span></div><div class='line' id='LC235'><span class="cm">   */</span></div><div class='line' id='LC236'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">printDetails</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC237'><br></div><div class='line' id='LC238'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC239'><span class="cm">   * Test whether there are bytes available to be read in the</span></div><div class='line' id='LC240'><span class="cm">   * FIFO buffers. This optimized version does not rely on interrupt</span></div><div class='line' id='LC241'><span class="cm">   * flags, but checks the actual FIFO buffers.</span></div><div class='line' id='LC242'><span class="cm">   *</span></div><div class='line' id='LC243'><span class="cm">   * @note Optimization: Interrupt flags are no longer cleared when available is called,</span></div><div class='line' id='LC244'><span class="cm">   * but will be reset only when the data is read from the FIFO buffers.</span></div><div class='line' id='LC245'><span class="cm">   *</span></div><div class='line' id='LC246'><span class="cm">   * @param[out] pipe_num Which pipe has the payload available</span></div><div class='line' id='LC247'><span class="cm">   * @return True if there is a payload available, false if none is</span></div><div class='line' id='LC248'><span class="cm">   */</span></div><div class='line' id='LC249'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">available</span><span class="p">(</span><span class="kt">uint8_t</span><span class="o">*</span> <span class="n">pipe_num</span><span class="p">);</span></div><div class='line' id='LC250'><br></div><div class='line' id='LC251'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC252'><span class="cm">   * Enter low-power mode</span></div><div class='line' id='LC253'><span class="cm">   *</span></div><div class='line' id='LC254'><span class="cm">   * To return to normal power mode, either write() some data or</span></div><div class='line' id='LC255'><span class="cm">   * startListening, or powerUp().</span></div><div class='line' id='LC256'><span class="cm">   *</span></div><div class='line' id='LC257'><span class="cm">   * @note Optimization: The radio will never enter power down unless instructed</span></div><div class='line' id='LC258'><span class="cm">   * by the MCU via this command.</span></div><div class='line' id='LC259'><span class="cm">   */</span></div><div class='line' id='LC260'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">powerDown</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC261'><br></div><div class='line' id='LC262'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC263'><span class="cm">   * Leave low-power mode - making radio more responsive</span></div><div class='line' id='LC264'><span class="cm">   *</span></div><div class='line' id='LC265'><span class="cm">   * To return to low power mode, call powerDown().</span></div><div class='line' id='LC266'><span class="cm">   */</span></div><div class='line' id='LC267'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">powerUp</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC268'><br></div><div class='line' id='LC269'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC270'><span class="cm">  * Write for single NOACK writes. Disables acknowledgements/autoretries for a single write.</span></div><div class='line' id='LC271'><span class="cm">  *</span></div><div class='line' id='LC272'><span class="cm">  * @note enableDynamicAck() must be called to enable this feature</span></div><div class='line' id='LC273'><span class="cm">  *</span></div><div class='line' id='LC274'><span class="cm">  * Can be used with enableAckPayload() to request a response</span></div><div class='line' id='LC275'><span class="cm">  * @see enableDynamicAck()</span></div><div class='line' id='LC276'><span class="cm">  * @see setAutoAck()</span></div><div class='line' id='LC277'><span class="cm">  * @see write()</span></div><div class='line' id='LC278'><span class="cm">  *</span></div><div class='line' id='LC279'><span class="cm">  * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC280'><span class="cm">  * @param len Number of bytes to be sent</span></div><div class='line' id='LC281'><span class="cm">  * @param multicast Request ACK (0), NOACK (1)</span></div><div class='line' id='LC282'><span class="cm">  */</span></div><div class='line' id='LC283'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">write</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">);</span></div><div class='line' id='LC284'><br></div><div class='line' id='LC285'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC286'><span class="cm">   * @note Optimization: New Command   *</span></div><div class='line' id='LC287'><span class="cm">   * This will not block until the 3 FIFO buffers are filled with data.</span></div><div class='line' id='LC288'><span class="cm">   * Once the FIFOs are full, writeFast will simply wait for success or</span></div><div class='line' id='LC289'><span class="cm">   * timeout, and return 1 or 0 respectively. From a user perspective, just</span></div><div class='line' id='LC290'><span class="cm">   * keep trying to send the same data. The library will keep auto retrying</span></div><div class='line' id='LC291'><span class="cm">   * the current payload using the built in functionality.</span></div><div class='line' id='LC292'><span class="cm">   * @warning It is important to never keep the nRF24L01 in TX mode for more than 4ms at a time. If the auto</span></div><div class='line' id='LC293'><span class="cm">   * retransmit is enabled, the nRF24L01 is never in TX mode long enough to disobey this rule. Allow the FIFO</span></div><div class='line' id='LC294'><span class="cm">   * to clear by issuing txStandBy() or ensure appropriate time between transmissions.</span></div><div class='line' id='LC295'><span class="cm">   *</span></div><div class='line' id='LC296'><span class="cm">   * ONLY max retry interrupt flags will be cleared when writeFast is called</span></div><div class='line' id='LC297'><span class="cm">   *</span></div><div class='line' id='LC298'><span class="cm">   * @code</span></div><div class='line' id='LC299'><span class="cm">   * Example (Partial blocking):</span></div><div class='line' id='LC300'><span class="cm">   *</span></div><div class='line' id='LC301'><span class="cm">   *			radio.writeFast(&amp;buf,32);  // Writes 1 payload to the buffers</span></div><div class='line' id='LC302'><span class="cm">   *			txStandBy();     		   // Returns 0 if failed. 1 if success. Blocks only until MAX_RT timeout or success. Data flushed on fail.</span></div><div class='line' id='LC303'><span class="cm">   *</span></div><div class='line' id='LC304'><span class="cm">   *			radio.writeFast(&amp;buf,32);  // Writes 1 payload to the buffers</span></div><div class='line' id='LC305'><span class="cm">   *			txStandBy(1000);		   // Using extended timeouts, returns 1 if success. Retries failed payloads for 1 seconds before returning 0.</span></div><div class='line' id='LC306'><span class="cm">   * @endcode</span></div><div class='line' id='LC307'><span class="cm">   *</span></div><div class='line' id='LC308'><span class="cm">   * @see txStandBy()</span></div><div class='line' id='LC309'><span class="cm">   * @see write()</span></div><div class='line' id='LC310'><span class="cm">   * @see writeBlocking()</span></div><div class='line' id='LC311'><span class="cm">   *</span></div><div class='line' id='LC312'><span class="cm">   * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC313'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC314'><span class="cm">   * @return True if the payload was delivered successfully false if not</span></div><div class='line' id='LC315'><span class="cm">   */</span></div><div class='line' id='LC316'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">writeFast</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">);</span></div><div class='line' id='LC317'><br></div><div class='line' id='LC318'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC319'><span class="cm">  * WriteFast for single NOACK writes. Disables acknowledgements/autoretries for a single write.</span></div><div class='line' id='LC320'><span class="cm">  *</span></div><div class='line' id='LC321'><span class="cm">  * @note enableDynamicAck() must be called to enable this feature</span></div><div class='line' id='LC322'><span class="cm">  * @see enableDynamicAck()</span></div><div class='line' id='LC323'><span class="cm">  * @see setAutoAck()</span></div><div class='line' id='LC324'><span class="cm">  *</span></div><div class='line' id='LC325'><span class="cm">  * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC326'><span class="cm">  * @param len Number of bytes to be sent</span></div><div class='line' id='LC327'><span class="cm">  * @param multicast Request ACK (0) or NOACK (1)</span></div><div class='line' id='LC328'><span class="cm">  */</span></div><div class='line' id='LC329'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">writeFast</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">);</span></div><div class='line' id='LC330'><br></div><div class='line' id='LC331'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC332'><span class="cm">   * @note Optimization: New Command</span></div><div class='line' id='LC333'><span class="cm">   * This function extends the auto-retry mechanism to any specified duration.</span></div><div class='line' id='LC334'><span class="cm">   * It will not block until the 3 FIFO buffers are filled with data.</span></div><div class='line' id='LC335'><span class="cm">   * If so the library will auto retry until a new payload is written</span></div><div class='line' id='LC336'><span class="cm">   * or the user specified timeout period is reached.</span></div><div class='line' id='LC337'><span class="cm">   * @warning It is important to never keep the nRF24L01 in TX mode for more than 4ms at a time. If the auto</span></div><div class='line' id='LC338'><span class="cm">   * retransmit is enabled, the nRF24L01 is never in TX mode long enough to disobey this rule. Allow the FIFO</span></div><div class='line' id='LC339'><span class="cm">   * to clear by issuing txStandBy() or ensure appropriate time between transmissions.</span></div><div class='line' id='LC340'><span class="cm">   *</span></div><div class='line' id='LC341'><span class="cm">   * ONLY max retry interrupt flags will be cleared when writeBlocking is called</span></div><div class='line' id='LC342'><span class="cm">   * @code</span></div><div class='line' id='LC343'><span class="cm">   * Example (Full blocking):</span></div><div class='line' id='LC344'><span class="cm">   *</span></div><div class='line' id='LC345'><span class="cm">   *			radio.writeBlocking(&amp;buf,32,1000); //Wait up to 1 second to write 1 payload to the buffers</span></div><div class='line' id='LC346'><span class="cm">   *			txStandBy(1000);     			   //Wait up to 1 second for the payload to send. Return 1 if ok, 0 if failed.</span></div><div class='line' id='LC347'><span class="cm">   *					  				   		   //Blocks only until user timeout or success. Data flushed on fail.</span></div><div class='line' id='LC348'><span class="cm">   * @endcode</span></div><div class='line' id='LC349'><span class="cm">   * @note If used from within an interrupt, the interrupt should be disabled until completion, and sei(); called to enable millis().</span></div><div class='line' id='LC350'><span class="cm">   * @see txStandBy()</span></div><div class='line' id='LC351'><span class="cm">   * @see write()</span></div><div class='line' id='LC352'><span class="cm">   * @see writeFast()</span></div><div class='line' id='LC353'><span class="cm">   *</span></div><div class='line' id='LC354'><span class="cm">   * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC355'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC356'><span class="cm">   * @param timeout User defined timeout in milliseconds.</span></div><div class='line' id='LC357'><span class="cm">   * @return True if the payload was loaded into the buffer successfully false if not</span></div><div class='line' id='LC358'><span class="cm">   */</span></div><div class='line' id='LC359'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">writeBlocking</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="kt">uint32_t</span> <span class="n">timeout</span> <span class="p">);</span></div><div class='line' id='LC360'><br></div><div class='line' id='LC361'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC362'><span class="cm">   * @note Optimization: New Command</span></div><div class='line' id='LC363'><span class="cm">   * This function should be called as soon as transmission is finished to</span></div><div class='line' id='LC364'><span class="cm">   * drop the radio back to STANDBY-I mode. If not issued, the radio will</span></div><div class='line' id='LC365'><span class="cm">   * remain in STANDBY-II mode which, per the data sheet, is not a recommended</span></div><div class='line' id='LC366'><span class="cm">   * operating mode.</span></div><div class='line' id='LC367'><span class="cm">   *</span></div><div class='line' id='LC368'><span class="cm">   * @note When transmitting data in rapid succession, it is still recommended by</span></div><div class='line' id='LC369'><span class="cm">   * the manufacturer to drop the radio out of TX or STANDBY-II mode if there is</span></div><div class='line' id='LC370'><span class="cm">   * time enough between sends for the FIFOs to empty.</span></div><div class='line' id='LC371'><span class="cm">   *</span></div><div class='line' id='LC372'><span class="cm">   * Relies on built-in auto retry functionality.</span></div><div class='line' id='LC373'><span class="cm">   *</span></div><div class='line' id='LC374'><span class="cm">   * @code</span></div><div class='line' id='LC375'><span class="cm">   * Example (Partial blocking):</span></div><div class='line' id='LC376'><span class="cm">   *</span></div><div class='line' id='LC377'><span class="cm">   *			radio.writeFast(&amp;buf,32);</span></div><div class='line' id='LC378'><span class="cm">   *			radio.writeFast(&amp;buf,32);</span></div><div class='line' id='LC379'><span class="cm">   *			radio.writeFast(&amp;buf,32);  //Fills the FIFO buffers up</span></div><div class='line' id='LC380'><span class="cm">   *			bool ok = txStandBy();     //Returns 0 if failed. 1 if success.</span></div><div class='line' id='LC381'><span class="cm">   *					  				   //Blocks only until MAX_RT timeout or success. Data flushed on fail.</span></div><div class='line' id='LC382'><span class="cm">   * @endcode</span></div><div class='line' id='LC383'><span class="cm">   * @see txStandBy(unsigned long timeout)</span></div><div class='line' id='LC384'><span class="cm">   * @return True if transmission is successful</span></div><div class='line' id='LC385'><span class="cm">   *</span></div><div class='line' id='LC386'><span class="cm">   */</span></div><div class='line' id='LC387'>&nbsp;&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">txStandBy</span><span class="p">();</span></div><div class='line' id='LC388'><br></div><div class='line' id='LC389'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC390'><span class="cm">   * @note Optimization: New Command</span></div><div class='line' id='LC391'><span class="cm">   *</span></div><div class='line' id='LC392'><span class="cm">   * This function allows extended blocking and auto-retries per a user defined timeout</span></div><div class='line' id='LC393'><span class="cm">   * @code</span></div><div class='line' id='LC394'><span class="cm">   *	Fully Blocking Example:</span></div><div class='line' id='LC395'><span class="cm">   *</span></div><div class='line' id='LC396'><span class="cm">   *			radio.writeFast(&amp;buf,32);</span></div><div class='line' id='LC397'><span class="cm">   *			radio.writeFast(&amp;buf,32);</span></div><div class='line' id='LC398'><span class="cm">   *			radio.writeFast(&amp;buf,32);   //Fills the FIFO buffers up</span></div><div class='line' id='LC399'><span class="cm">   *			bool ok = txStandBy(1000);  //Returns 0 if failed after 1 second of retries. 1 if success.</span></div><div class='line' id='LC400'><span class="cm">   *					  				    //Blocks only until user defined timeout or success. Data flushed on fail.</span></div><div class='line' id='LC401'><span class="cm">   * @endcode</span></div><div class='line' id='LC402'><span class="cm">   * @note If used from within an interrupt, the interrupt should be disabled until completion, and sei(); called to enable millis().</span></div><div class='line' id='LC403'><span class="cm">   * @param timeout Number of milliseconds to retry failed payloads</span></div><div class='line' id='LC404'><span class="cm">   * @return True if transmission is successful</span></div><div class='line' id='LC405'><span class="cm">   *</span></div><div class='line' id='LC406'><span class="cm">   */</span></div><div class='line' id='LC407'>&nbsp;&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">txStandBy</span><span class="p">(</span><span class="kt">uint32_t</span> <span class="n">timeout</span><span class="p">);</span></div><div class='line' id='LC408'><br></div><div class='line' id='LC409'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC410'><span class="cm">   * Write an ack payload for the specified pipe</span></div><div class='line' id='LC411'><span class="cm">   *</span></div><div class='line' id='LC412'><span class="cm">   * The next time a message is received on @p pipe, the data in @p buf will</span></div><div class='line' id='LC413'><span class="cm">   * be sent back in the acknowledgement.</span></div><div class='line' id='LC414'><span class="cm">   *</span></div><div class='line' id='LC415'><span class="cm">   * @warning According to the data sheet, only three of these can be pending</span></div><div class='line' id='LC416'><span class="cm">   * at any time as there are only 3 FIFO buffers.</span></div><div class='line' id='LC417'><span class="cm">   *</span></div><div class='line' id='LC418'><span class="cm">   * @param pipe Which pipe# (typically 1-5) will get this response.</span></div><div class='line' id='LC419'><span class="cm">   * @param buf Pointer to data that is sent</span></div><div class='line' id='LC420'><span class="cm">   * @param len Length of the data to send, up to 32 bytes max.  Not affected</span></div><div class='line' id='LC421'><span class="cm">   * by the static payload set by setPayloadSize().</span></div><div class='line' id='LC422'><span class="cm">   */</span></div><div class='line' id='LC423'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">writeAckPayload</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pipe</span><span class="p">,</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC424'><br></div><div class='line' id='LC425'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC426'><span class="cm">   * Enable dynamic ACKs (single write multicasting) for chosen messages</span></div><div class='line' id='LC427'><span class="cm">   *</span></div><div class='line' id='LC428'><span class="cm">   * @note To enable full multicasting or per-pipe multicast, use setAutoAck()</span></div><div class='line' id='LC429'><span class="cm">   *</span></div><div class='line' id='LC430'><span class="cm">   * @warning This MUST be called prior to attempting single write NOACK calls</span></div><div class='line' id='LC431'><span class="cm">   * @code</span></div><div class='line' id='LC432'><span class="cm">   * radio.enableDynamicAck();</span></div><div class='line' id='LC433'><span class="cm">   * radio.write(&amp;data,32,1);  // Sends a payload with no acknowledgement requested</span></div><div class='line' id='LC434'><span class="cm">   * radio.write(&amp;data,32,0);  // Sends a payload using auto-retry/autoACK</span></div><div class='line' id='LC435'><span class="cm">   * @endcode</span></div><div class='line' id='LC436'><span class="cm">   */</span></div><div class='line' id='LC437'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">enableDynamicAck</span><span class="p">();</span></div><div class='line' id='LC438'><br></div><div class='line' id='LC439'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC440'><span class="cm">   * Determine if an ack payload was received in the most recent call to</span></div><div class='line' id='LC441'><span class="cm">   * write().</span></div><div class='line' id='LC442'><span class="cm">   *</span></div><div class='line' id='LC443'><span class="cm">   * Call read() to retrieve the ack payload.</span></div><div class='line' id='LC444'><span class="cm">   *</span></div><div class='line' id='LC445'><span class="cm">   * @note Optimization: Calling this function NO LONGER clears the interrupt</span></div><div class='line' id='LC446'><span class="cm">   * flag. The new functionality checks the RX FIFO buffer for an ACK payload</span></div><div class='line' id='LC447'><span class="cm">   * instead of relying on interrupt flags.Reading the payload will clear the flags.</span></div><div class='line' id='LC448'><span class="cm">   *</span></div><div class='line' id='LC449'><span class="cm">   * @return True if an ack payload is available.</span></div><div class='line' id='LC450'><span class="cm">   */</span></div><div class='line' id='LC451'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">isAckPayloadAvailable</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC452'><br></div><div class='line' id='LC453'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC454'><span class="cm">   * Call this when you get an interrupt to find out why</span></div><div class='line' id='LC455'><span class="cm">   *</span></div><div class='line' id='LC456'><span class="cm">   * Tells you what caused the interrupt, and clears the state of</span></div><div class='line' id='LC457'><span class="cm">   * interrupts.</span></div><div class='line' id='LC458'><span class="cm">   *</span></div><div class='line' id='LC459'><span class="cm">   * @param[out] tx_ok The send was successful (TX_DS)</span></div><div class='line' id='LC460'><span class="cm">   * @param[out] tx_fail The send failed, too many retries (MAX_RT)</span></div><div class='line' id='LC461'><span class="cm">   * @param[out] rx_ready There is a message waiting to be read (RX_DS)</span></div><div class='line' id='LC462'><span class="cm">   */</span></div><div class='line' id='LC463'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">whatHappened</span><span class="p">(</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">tx_ok</span><span class="p">,</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">tx_fail</span><span class="p">,</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">rx_ready</span><span class="p">);</span></div><div class='line' id='LC464'><br></div><div class='line' id='LC465'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC466'><span class="cm">   * Non-blocking write to the open writing pipe used for buffered writes</span></div><div class='line' id='LC467'><span class="cm">   *</span></div><div class='line' id='LC468'><span class="cm">   * @note Optimization: This function now leaves the CE pin high, so the radio</span></div><div class='line' id='LC469'><span class="cm">   * will remain in TX or STANDBY-II Mode until a txStandBy() command is issued.</span></div><div class='line' id='LC470'><span class="cm">   * This allows the chip to be used to its full potential in TX mode.</span></div><div class='line' id='LC471'><span class="cm">   * @warning It is important to never keep the nRF24L01 in TX mode for more than 4ms at a time. If the auto</span></div><div class='line' id='LC472'><span class="cm">   * retransmit is enabled, the nRF24L01 is never in TX mode long enough to disobey this rule. Allow the FIFO</span></div><div class='line' id='LC473'><span class="cm">   * to clear by issuing txStandBy() or ensure appropriate time between transmissions.</span></div><div class='line' id='LC474'><span class="cm">   *</span></div><div class='line' id='LC475'><span class="cm">   * @see write()</span></div><div class='line' id='LC476'><span class="cm">   * @see writeFast()</span></div><div class='line' id='LC477'><span class="cm">   * @see startWrite()</span></div><div class='line' id='LC478'><span class="cm">   * @see writeBlocking()</span></div><div class='line' id='LC479'><span class="cm">   *</span></div><div class='line' id='LC480'><span class="cm">   * For single noAck writes see:</span></div><div class='line' id='LC481'><span class="cm">   * @see enableDynamicAck()</span></div><div class='line' id='LC482'><span class="cm">   * @see setAutoAck()</span></div><div class='line' id='LC483'><span class="cm">   *</span></div><div class='line' id='LC484'><span class="cm">   * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC485'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC486'><span class="cm">   * @param multicast Request ACK (0) or NOACK (1)</span></div><div class='line' id='LC487'><span class="cm">   * @return True if the payload was delivered successfully false if not</span></div><div class='line' id='LC488'><span class="cm">   */</span></div><div class='line' id='LC489'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">startFastWrite</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">);</span></div><div class='line' id='LC490'><br></div><div class='line' id='LC491'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC492'><span class="cm">   * Non-blocking write to the open writing pipe</span></div><div class='line' id='LC493'><span class="cm">   *</span></div><div class='line' id='LC494'><span class="cm">   * Just like write(), but it returns immediately. To find out what happened</span></div><div class='line' id='LC495'><span class="cm">   * to the send, catch the IRQ and then call whatHappened().</span></div><div class='line' id='LC496'><span class="cm">   *</span></div><div class='line' id='LC497'><span class="cm">   * @note Optimization: This function again behaves as it did previously for backwards-compatibility.</span></div><div class='line' id='LC498'><span class="cm">   * with user code. The library uses startFastWrite() internally.</span></div><div class='line' id='LC499'><span class="cm">   * This is mainly used for single-payload transactions.</span></div><div class='line' id='LC500'><span class="cm">   *</span></div><div class='line' id='LC501'><span class="cm">   * @see write()</span></div><div class='line' id='LC502'><span class="cm">   * @see writeFast()</span></div><div class='line' id='LC503'><span class="cm">   * @see startFastWrite()</span></div><div class='line' id='LC504'><span class="cm">   * @see whatHappened()</span></div><div class='line' id='LC505'><span class="cm">   *</span></div><div class='line' id='LC506'><span class="cm">   * For single noAck writes see:</span></div><div class='line' id='LC507'><span class="cm">   * @see enableDynamicAck()</span></div><div class='line' id='LC508'><span class="cm">   * @see setAutoAck()</span></div><div class='line' id='LC509'><span class="cm">   *</span></div><div class='line' id='LC510'><span class="cm">   * @param buf Pointer to the data to be sent</span></div><div class='line' id='LC511'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC512'><span class="cm">   * @param multicast Request ACK (0) or NOACK (1)</span></div><div class='line' id='LC513'><span class="cm">   *</span></div><div class='line' id='LC514'><span class="cm">   */</span></div><div class='line' id='LC515'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">startWrite</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">);</span></div><div class='line' id='LC516'><br></div><div class='line' id='LC517'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC518'><span class="cm">   * Optimization: New Command</span></div><div class='line' id='LC519'><span class="cm">   *</span></div><div class='line' id='LC520'><span class="cm">   * This function is mainly used internally to take advantage of the auto payload</span></div><div class='line' id='LC521'><span class="cm">   * re-use functionality of the chip, but can be beneficial to users as well.</span></div><div class='line' id='LC522'><span class="cm">   *</span></div><div class='line' id='LC523'><span class="cm">   * The function will instruct the radio to re-use the data in the FIFO buffers,</span></div><div class='line' id='LC524'><span class="cm">   * and instructs the radio to re-send once the timeout limit has been reached.</span></div><div class='line' id='LC525'><span class="cm">   * Used by writeFast and writeBlocking to initiate retries when a TX failure</span></div><div class='line' id='LC526'><span class="cm">   * occurs. Retries are automatically initiated except with the standard write().</span></div><div class='line' id='LC527'><span class="cm">   * This way, data is not flushed from the buffer until switching between modes.</span></div><div class='line' id='LC528'><span class="cm">   *</span></div><div class='line' id='LC529'><span class="cm">   * @note This is to be used AFTER auto-retry fails if wanting to resend</span></div><div class='line' id='LC530'><span class="cm">   * using the built-in payload reuse features.</span></div><div class='line' id='LC531'><span class="cm">   * After issuing reUseTX(), it will keep reending the same payload forever or until</span></div><div class='line' id='LC532'><span class="cm">   * a payload is written to the FIFO, or a flush_tx command is given.</span></div><div class='line' id='LC533'><span class="cm">   */</span></div><div class='line' id='LC534'>&nbsp;&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">reUseTX</span><span class="p">();</span></div><div class='line' id='LC535'><br></div><div class='line' id='LC536'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC537'><span class="cm">   * Empty the transmit buffer</span></div><div class='line' id='LC538'><span class="cm">   *</span></div><div class='line' id='LC539'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC540'><span class="cm">   */</span></div><div class='line' id='LC541'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">flush_tx</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC542'><br></div><div class='line' id='LC543'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC544'><span class="cm">   * Test whether there was a carrier on the line for the</span></div><div class='line' id='LC545'><span class="cm">   * previous listening period.</span></div><div class='line' id='LC546'><span class="cm">   *</span></div><div class='line' id='LC547'><span class="cm">   * Useful to check for interference on the current channel.</span></div><div class='line' id='LC548'><span class="cm">   *</span></div><div class='line' id='LC549'><span class="cm">   * @return true if was carrier, false if not</span></div><div class='line' id='LC550'><span class="cm">   */</span></div><div class='line' id='LC551'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">testCarrier</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC552'><br></div><div class='line' id='LC553'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC554'><span class="cm">   * Test whether a signal (carrier or otherwise) greater than</span></div><div class='line' id='LC555'><span class="cm">   * or equal to -64dBm is present on the channel. Valid only</span></div><div class='line' id='LC556'><span class="cm">   * on nRF24L01P (+) hardware. On nRF24L01, use testCarrier().</span></div><div class='line' id='LC557'><span class="cm">   *</span></div><div class='line' id='LC558'><span class="cm">   * Useful to check for interference on the current channel and</span></div><div class='line' id='LC559'><span class="cm">   * channel hopping strategies.</span></div><div class='line' id='LC560'><span class="cm">   *</span></div><div class='line' id='LC561'><span class="cm">   * @return true if signal =&gt; -64dBm, false if not</span></div><div class='line' id='LC562'><span class="cm">   */</span></div><div class='line' id='LC563'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">testRPD</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC564'><br></div><div class='line' id='LC565'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC566'><span class="cm">   * Test whether this is a real radio, or a mock shim for</span></div><div class='line' id='LC567'><span class="cm">   * debugging.  Setting either pin to 0xff is the way to</span></div><div class='line' id='LC568'><span class="cm">   * indicate that this is not a real radio.</span></div><div class='line' id='LC569'><span class="cm">   *</span></div><div class='line' id='LC570'><span class="cm">   * @return true if this is a legitimate radio</span></div><div class='line' id='LC571'><span class="cm">   */</span></div><div class='line' id='LC572'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">isValid</span><span class="p">()</span> <span class="p">{</span> <span class="k">return</span> <span class="n">ce_pin</span> <span class="o">!=</span> <span class="mh">0xff</span> <span class="o">&amp;&amp;</span> <span class="n">csn_pin</span> <span class="o">!=</span> <span class="mh">0xff</span><span class="p">;</span> <span class="p">}</span></div><div class='line' id='LC573'><br></div><div class='line' id='LC574'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC575'><span class="cm">  * The radio will generate interrupt signals when a transmission is complete,</span></div><div class='line' id='LC576'><span class="cm">  * a transmission fails, or a payload is received. This allows users to mask</span></div><div class='line' id='LC577'><span class="cm">  * those interrupts to prevent them from generating a signal on the interrupt</span></div><div class='line' id='LC578'><span class="cm">  * pin.</span></div><div class='line' id='LC579'><span class="cm">  *</span></div><div class='line' id='LC580'><span class="cm">  * @code</span></div><div class='line' id='LC581'><span class="cm">  * 	Mask all interrupts except the receive interrupt:</span></div><div class='line' id='LC582'><span class="cm">  *</span></div><div class='line' id='LC583'><span class="cm">  *		radio.maskIRQ(1,1,0);</span></div><div class='line' id='LC584'><span class="cm">  * @endcode</span></div><div class='line' id='LC585'><span class="cm">  *</span></div><div class='line' id='LC586'><span class="cm">  * @param tx_ok  Mask transmission complete interrupts</span></div><div class='line' id='LC587'><span class="cm">  * @param tx_fail  Mask transmit failure interrupts</span></div><div class='line' id='LC588'><span class="cm">  * @param rx_ready Mask payload received interrupts</span></div><div class='line' id='LC589'><span class="cm">  */</span></div><div class='line' id='LC590'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">maskIRQ</span><span class="p">(</span><span class="kt">bool</span> <span class="n">tx_ok</span><span class="p">,</span><span class="kt">bool</span> <span class="n">tx_fail</span><span class="p">,</span><span class="kt">bool</span> <span class="n">rx_ready</span><span class="p">);</span></div><div class='line' id='LC591'><br></div><div class='line' id='LC592'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC593'><span class="cm">  * Set the address width from 3 to 5 bytes (24, 32 or 40 bit)</span></div><div class='line' id='LC594'><span class="cm">  *</span></div><div class='line' id='LC595'><span class="cm">  * @param a_width The address width to use: 3,4 or 5</span></div><div class='line' id='LC596'><span class="cm">  */</span></div><div class='line' id='LC597'><br></div><div class='line' id='LC598'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setAddressWidth</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">a_width</span><span class="p">);</span></div><div class='line' id='LC599'><br></div><div class='line' id='LC600'>&nbsp;&nbsp;<span class="cm">/**@}*/</span></div><div class='line' id='LC601'><br></div><div class='line' id='LC602'>&nbsp;&nbsp;<span class="cm">/**@}*/</span></div><div class='line' id='LC603'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC604'><span class="cm">   * @name Optional Configurators</span></div><div class='line' id='LC605'><span class="cm">   *</span></div><div class='line' id='LC606'><span class="cm">   *  Methods you can use to get or set the configuration of the chip.</span></div><div class='line' id='LC607'><span class="cm">   *  None are required.  Calling begin() sets up a reasonable set of</span></div><div class='line' id='LC608'><span class="cm">   *  defaults.</span></div><div class='line' id='LC609'><span class="cm">   */</span></div><div class='line' id='LC610'>&nbsp;&nbsp;<span class="cm">/**@{*/</span></div><div class='line' id='LC611'><br></div><div class='line' id='LC612'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC613'><span class="cm">   * Set the number and delay of retries upon failed submit</span></div><div class='line' id='LC614'><span class="cm">   *</span></div><div class='line' id='LC615'><span class="cm">   * @param delay How long to wait between each retry, in multiples of 250us,</span></div><div class='line' id='LC616'><span class="cm">   * max is 15.  0 means 250us, 15 means 4000us.</span></div><div class='line' id='LC617'><span class="cm">   * @param count How many retries before giving up, max 15</span></div><div class='line' id='LC618'><span class="cm">   */</span></div><div class='line' id='LC619'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setRetries</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">delay</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">count</span><span class="p">);</span></div><div class='line' id='LC620'><br></div><div class='line' id='LC621'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC622'><span class="cm">   * Set RF communication channel</span></div><div class='line' id='LC623'><span class="cm">   *</span></div><div class='line' id='LC624'><span class="cm">   * @param channel Which RF channel to communicate on, 0-127</span></div><div class='line' id='LC625'><span class="cm">   */</span></div><div class='line' id='LC626'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setChannel</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">channel</span><span class="p">);</span></div><div class='line' id='LC627'><br></div><div class='line' id='LC628'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC629'><span class="cm">   * Set Static Payload Size</span></div><div class='line' id='LC630'><span class="cm">   *</span></div><div class='line' id='LC631'><span class="cm">   * This implementation uses a pre-stablished fixed payload size for all</span></div><div class='line' id='LC632'><span class="cm">   * transmissions.  If this method is never called, the driver will always</span></div><div class='line' id='LC633'><span class="cm">   * transmit the maximum payload size (32 bytes), no matter how much</span></div><div class='line' id='LC634'><span class="cm">   * was sent to write().</span></div><div class='line' id='LC635'><span class="cm">   *</span></div><div class='line' id='LC636'><span class="cm">   * @todo Implement variable-sized payloads feature</span></div><div class='line' id='LC637'><span class="cm">   *</span></div><div class='line' id='LC638'><span class="cm">   * @param size The number of bytes in the payload</span></div><div class='line' id='LC639'><span class="cm">   */</span></div><div class='line' id='LC640'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setPayloadSize</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">size</span><span class="p">);</span></div><div class='line' id='LC641'><br></div><div class='line' id='LC642'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC643'><span class="cm">   * Get Static Payload Size</span></div><div class='line' id='LC644'><span class="cm">   *</span></div><div class='line' id='LC645'><span class="cm">   * @see setPayloadSize()</span></div><div class='line' id='LC646'><span class="cm">   *</span></div><div class='line' id='LC647'><span class="cm">   * @return The number of bytes in the payload</span></div><div class='line' id='LC648'><span class="cm">   */</span></div><div class='line' id='LC649'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">getPayloadSize</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC650'><br></div><div class='line' id='LC651'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC652'><span class="cm">   * Get Dynamic Payload Size</span></div><div class='line' id='LC653'><span class="cm">   *</span></div><div class='line' id='LC654'><span class="cm">   * For dynamic payloads, this pulls the size of the payload off</span></div><div class='line' id='LC655'><span class="cm">   * the chip</span></div><div class='line' id='LC656'><span class="cm">   *</span></div><div class='line' id='LC657'><span class="cm">   * @note Optimization: Corrupt packets are now detected and flushed per the</span></div><div class='line' id='LC658'><span class="cm">   * manufacturer.</span></div><div class='line' id='LC659'><span class="cm">   *</span></div><div class='line' id='LC660'><span class="cm">   * @return Payload length of last-received dynamic payload</span></div><div class='line' id='LC661'><span class="cm">   */</span></div><div class='line' id='LC662'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">getDynamicPayloadSize</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC663'><br></div><div class='line' id='LC664'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC665'><span class="cm">   * Enable custom payloads on the acknowledge packets</span></div><div class='line' id='LC666'><span class="cm">   *</span></div><div class='line' id='LC667'><span class="cm">   * Ack payloads are a handy way to return data back to senders without</span></div><div class='line' id='LC668'><span class="cm">   * manually changing the radio modes on both units.</span></div><div class='line' id='LC669'><span class="cm">   *</span></div><div class='line' id='LC670'><span class="cm">   * @see examples/pingpair_pl/pingpair_pl.pde</span></div><div class='line' id='LC671'><span class="cm">   */</span></div><div class='line' id='LC672'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">enableAckPayload</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC673'><br></div><div class='line' id='LC674'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC675'><span class="cm">   * Enable dynamically-sized payloads</span></div><div class='line' id='LC676'><span class="cm">   *</span></div><div class='line' id='LC677'><span class="cm">   * This way you don&#39;t always have to send large packets just to send them</span></div><div class='line' id='LC678'><span class="cm">   * once in a while.  This enables dynamic payloads on ALL pipes.</span></div><div class='line' id='LC679'><span class="cm">   *</span></div><div class='line' id='LC680'><span class="cm">   * @see examples/pingpair_pl/pingpair_dyn.pde</span></div><div class='line' id='LC681'><span class="cm">   */</span></div><div class='line' id='LC682'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">enableDynamicPayloads</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC683'><br></div><div class='line' id='LC684'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC685'><span class="cm">   * Determine whether the hardware is an nRF24L01+ or not.</span></div><div class='line' id='LC686'><span class="cm">   *</span></div><div class='line' id='LC687'><span class="cm">   * @return true if the hardware is nRF24L01+ (or compatible) and false</span></div><div class='line' id='LC688'><span class="cm">   * if its not.</span></div><div class='line' id='LC689'><span class="cm">   */</span></div><div class='line' id='LC690'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">isPVariant</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC691'><br></div><div class='line' id='LC692'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC693'><span class="cm">   * Enable or disable auto-acknowlede packets</span></div><div class='line' id='LC694'><span class="cm">   *</span></div><div class='line' id='LC695'><span class="cm">   * This is enabled by default, so it&#39;s only needed if you want to turn</span></div><div class='line' id='LC696'><span class="cm">   * it off for some reason.</span></div><div class='line' id='LC697'><span class="cm">   *</span></div><div class='line' id='LC698'><span class="cm">   * @param enable Whether to enable (true) or disable (false) auto-acks</span></div><div class='line' id='LC699'><span class="cm">   */</span></div><div class='line' id='LC700'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setAutoAck</span><span class="p">(</span><span class="kt">bool</span> <span class="n">enable</span><span class="p">);</span></div><div class='line' id='LC701'><br></div><div class='line' id='LC702'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC703'><span class="cm">   * Enable or disable auto-acknowlede packets on a per pipeline basis.</span></div><div class='line' id='LC704'><span class="cm">   *</span></div><div class='line' id='LC705'><span class="cm">   * AA is enabled by default, so it&#39;s only needed if you want to turn</span></div><div class='line' id='LC706'><span class="cm">   * it off/on for some reason on a per pipeline basis.</span></div><div class='line' id='LC707'><span class="cm">   *</span></div><div class='line' id='LC708'><span class="cm">   * @param pipe Which pipeline to modify</span></div><div class='line' id='LC709'><span class="cm">   * @param enable Whether to enable (true) or disable (false) auto-acks</span></div><div class='line' id='LC710'><span class="cm">   */</span></div><div class='line' id='LC711'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setAutoAck</span><span class="p">(</span> <span class="kt">uint8_t</span> <span class="n">pipe</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">enable</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC712'><br></div><div class='line' id='LC713'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC714'><span class="cm">   * Set Power Amplifier (PA) level to one of four levels:</span></div><div class='line' id='LC715'><span class="cm">   * RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX</span></div><div class='line' id='LC716'><span class="cm">   *</span></div><div class='line' id='LC717'><span class="cm">   * The power levels correspond to the following output levels respectively:</span></div><div class='line' id='LC718'><span class="cm">   * NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm</span></div><div class='line' id='LC719'><span class="cm">   *</span></div><div class='line' id='LC720'><span class="cm">   * SI24R1: -6dBm, 0dBm, 3dBM, and 7dBm.</span></div><div class='line' id='LC721'><span class="cm">   *</span></div><div class='line' id='LC722'><span class="cm">   * @param level Desired PA level.</span></div><div class='line' id='LC723'><span class="cm">   */</span></div><div class='line' id='LC724'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setPALevel</span> <span class="p">(</span> <span class="kt">uint8_t</span> <span class="n">level</span> <span class="p">);</span></div><div class='line' id='LC725'><br></div><div class='line' id='LC726'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC727'><span class="cm">   * Fetches the current PA level.</span></div><div class='line' id='LC728'><span class="cm">   *</span></div><div class='line' id='LC729'><span class="cm">   * NRF24L01: -18dBm, -12dBm, -6dBm and 0dBm</span></div><div class='line' id='LC730'><span class="cm">   * SI24R1:   -6dBm, 0dBm, 3dBm, 7dBm</span></div><div class='line' id='LC731'><span class="cm">   *</span></div><div class='line' id='LC732'><span class="cm">   * @return Returns values 0 to 3 representing the PA Level.</span></div><div class='line' id='LC733'><span class="cm">   */</span></div><div class='line' id='LC734'>&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">getPALevel</span><span class="p">(</span> <span class="kt">void</span> <span class="p">);</span></div><div class='line' id='LC735'><br></div><div class='line' id='LC736'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC737'><span class="cm">   * Set the transmission data rate</span></div><div class='line' id='LC738'><span class="cm">   *</span></div><div class='line' id='LC739'><span class="cm">   * @warning setting RF24_250KBPS will fail for non-plus units</span></div><div class='line' id='LC740'><span class="cm">   *</span></div><div class='line' id='LC741'><span class="cm">   * @param speed RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps</span></div><div class='line' id='LC742'><span class="cm">   * @return true if the change was successful</span></div><div class='line' id='LC743'><span class="cm">   */</span></div><div class='line' id='LC744'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">setDataRate</span><span class="p">(</span><span class="n">rf24_datarate_e</span> <span class="n">speed</span><span class="p">);</span></div><div class='line' id='LC745'><br></div><div class='line' id='LC746'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC747'><span class="cm">   * Fetches the transmission data rate</span></div><div class='line' id='LC748'><span class="cm">   *</span></div><div class='line' id='LC749'><span class="cm">   * @return Returns the hardware&#39;s currently configured datarate. The value</span></div><div class='line' id='LC750'><span class="cm">   * is one of 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS, as defined in the</span></div><div class='line' id='LC751'><span class="cm">   * rf24_datarate_e enum.</span></div><div class='line' id='LC752'><span class="cm">   */</span></div><div class='line' id='LC753'>&nbsp;&nbsp;<span class="n">rf24_datarate_e</span> <span class="nf">getDataRate</span><span class="p">(</span> <span class="kt">void</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC754'><br></div><div class='line' id='LC755'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC756'><span class="cm">   * Set the CRC length</span></div><div class='line' id='LC757'><span class="cm">   *</span></div><div class='line' id='LC758'><span class="cm">   * @param length RF24_CRC_8 for 8-bit or RF24_CRC_16 for 16-bit</span></div><div class='line' id='LC759'><span class="cm">   */</span></div><div class='line' id='LC760'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">setCRCLength</span><span class="p">(</span><span class="n">rf24_crclength_e</span> <span class="n">length</span><span class="p">);</span></div><div class='line' id='LC761'><br></div><div class='line' id='LC762'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC763'><span class="cm">   * Get the CRC length</span></div><div class='line' id='LC764'><span class="cm">   *</span></div><div class='line' id='LC765'><span class="cm">   * @return RF24_DISABLED if disabled or RF24_CRC_8 for 8-bit or RF24_CRC_16 for 16-bit</span></div><div class='line' id='LC766'><span class="cm">   */</span></div><div class='line' id='LC767'>&nbsp;&nbsp;<span class="n">rf24_crclength_e</span> <span class="nf">getCRCLength</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC768'><br></div><div class='line' id='LC769'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC770'><span class="cm">   * Disable CRC validation</span></div><div class='line' id='LC771'><span class="cm">   *</span></div><div class='line' id='LC772'><span class="cm">   */</span></div><div class='line' id='LC773'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">disableCRC</span><span class="p">(</span> <span class="kt">void</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC774'>&nbsp;&nbsp;</div><div class='line' id='LC775'>&nbsp;&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC776'><span class="cm">   * Enable error detection by un-commenting #define FAILURE_HANDLING in RF24_config.h</span></div><div class='line' id='LC777'><span class="cm">   * If a failure has been detected, it usually indicates a hardware issue. By default the library</span></div><div class='line' id='LC778'><span class="cm">   * will cease operation when a failure is detected.  </span></div><div class='line' id='LC779'><span class="cm">   * This should allow advanced users to detect and resolve intermittent hardware issues.  </span></div><div class='line' id='LC780'><span class="cm">   *   </span></div><div class='line' id='LC781'><span class="cm">   * In most cases, the radio must be re-enabled via radio.begin(); and the appropriate settings</span></div><div class='line' id='LC782'><span class="cm">   * applied after a failure occurs, if wanting to re-enable the device immediately.</span></div><div class='line' id='LC783'><span class="cm">   * </span></div><div class='line' id='LC784'><span class="cm">   * Usage: (Failure handling must be enabled per above)</span></div><div class='line' id='LC785'><span class="cm">   *  @code</span></div><div class='line' id='LC786'><span class="cm">   *  if(radio.failureDetected){ </span></div><div class='line' id='LC787'><span class="cm">   *    radio.begin(); 					     // Attempt to re-configure the radio with defaults</span></div><div class='line' id='LC788'><span class="cm">   *    radio.failureDetected = 0;		     // Reset the detection value</span></div><div class='line' id='LC789'><span class="cm">   *	radio.openWritingPipe(addresses[1]); // Re-configure pipe addresses</span></div><div class='line' id='LC790'><span class="cm">    *   radio.openReadingPipe(1,addresses[0]);</span></div><div class='line' id='LC791'><span class="cm">   *    report_failure();               	 // Blink leds, send a message, etc. to indicate failure</span></div><div class='line' id='LC792'><span class="cm">   *  }</span></div><div class='line' id='LC793'><span class="cm">   * @endcode</span></div><div class='line' id='LC794'><span class="cm">  */</span></div><div class='line' id='LC795'><span class="cp">  #if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC796'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span> <span class="n">failureDetected</span><span class="p">;</span> </div><div class='line' id='LC797'>&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC798'>&nbsp;&nbsp;<span class="cm">/**@}*/</span></div><div class='line' id='LC799'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC800'><span class="cm">   * @name Deprecated</span></div><div class='line' id='LC801'><span class="cm">   *</span></div><div class='line' id='LC802'><span class="cm">   *  Methods provided for backwards compabibility.</span></div><div class='line' id='LC803'><span class="cm">   */</span></div><div class='line' id='LC804'>&nbsp;&nbsp;<span class="cm">/**@{*/</span></div><div class='line' id='LC805'><br></div><div class='line' id='LC806'><br></div><div class='line' id='LC807'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC808'><span class="cm">   * Open a pipe for reading</span></div><div class='line' id='LC809'><span class="cm">   * @note For compatibility with old code only, see new function</span></div><div class='line' id='LC810'><span class="cm">   *</span></div><div class='line' id='LC811'><span class="cm">   * @warning Pipes 1-5 should share the first 32 bits.</span></div><div class='line' id='LC812'><span class="cm">   * Only the least significant byte should be unique, e.g.</span></div><div class='line' id='LC813'><span class="cm">   * @code</span></div><div class='line' id='LC814'><span class="cm">   *   openReadingPipe(1,0xF0F0F0F0AA);</span></div><div class='line' id='LC815'><span class="cm">   *   openReadingPipe(2,0xF0F0F0F066);</span></div><div class='line' id='LC816'><span class="cm">   * @endcode</span></div><div class='line' id='LC817'><span class="cm">   *</span></div><div class='line' id='LC818'><span class="cm">   * @warning Pipe 0 is also used by the writing pipe.  So if you open</span></div><div class='line' id='LC819'><span class="cm">   * pipe 0 for reading, and then startListening(), it will overwrite the</span></div><div class='line' id='LC820'><span class="cm">   * writing pipe.  Ergo, do an openWritingPipe() again before write().</span></div><div class='line' id='LC821'><span class="cm">   *</span></div><div class='line' id='LC822'><span class="cm">   * @param number Which pipe# to open, 0-5.</span></div><div class='line' id='LC823'><span class="cm">   * @param address The 40-bit address of the pipe to open.</span></div><div class='line' id='LC824'><span class="cm">   */</span></div><div class='line' id='LC825'>&nbsp;&nbsp;<span class="kt">void</span> <span class="n">openReadingPipe</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">number</span><span class="p">,</span> <span class="kt">uint64_t</span> <span class="n">address</span><span class="p">);</span></div><div class='line' id='LC826'><br></div><div class='line' id='LC827'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC828'><span class="cm">   * Open a pipe for writing</span></div><div class='line' id='LC829'><span class="cm">   * @note For compatibility with old code only, see new function</span></div><div class='line' id='LC830'><span class="cm">   * Addresses are 40-bit hex values, e.g.:</span></div><div class='line' id='LC831'><span class="cm">   *</span></div><div class='line' id='LC832'><span class="cm">   * @code</span></div><div class='line' id='LC833'><span class="cm">   *   openWritingPipe(0xF0F0F0F0F0);</span></div><div class='line' id='LC834'><span class="cm">   * @endcode</span></div><div class='line' id='LC835'><span class="cm">   *</span></div><div class='line' id='LC836'><span class="cm">   * @param address The 40-bit address of the pipe to open.</span></div><div class='line' id='LC837'><span class="cm">   */</span></div><div class='line' id='LC838'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">openWritingPipe</span><span class="p">(</span><span class="kt">uint64_t</span> <span class="n">address</span><span class="p">);</span></div><div class='line' id='LC839'><br></div><div class='line' id='LC840'><span class="k">private</span><span class="o">:</span></div><div class='line' id='LC841'><br></div><div class='line' id='LC842'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC843'><span class="cm">   * @name Low-level internal interface.</span></div><div class='line' id='LC844'><span class="cm">   *</span></div><div class='line' id='LC845'><span class="cm">   *  Protected methods that address the chip directly.  Regular users cannot</span></div><div class='line' id='LC846'><span class="cm">   *  ever call these.  They are documented for completeness and for developers who</span></div><div class='line' id='LC847'><span class="cm">   *  may want to extend this class.</span></div><div class='line' id='LC848'><span class="cm">   */</span></div><div class='line' id='LC849'>&nbsp;&nbsp;<span class="cm">/**@{*/</span></div><div class='line' id='LC850'><br></div><div class='line' id='LC851'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC852'><span class="cm">   * Set chip select pin</span></div><div class='line' id='LC853'><span class="cm">   *</span></div><div class='line' id='LC854'><span class="cm">   * Running SPI bus at PI_CLOCK_DIV2 so we don&#39;t waste time transferring data</span></div><div class='line' id='LC855'><span class="cm">   * and best of all, we make use of the radio&#39;s FIFO buffers. A lower speed</span></div><div class='line' id='LC856'><span class="cm">   * means we&#39;re less likely to effectively leverage our FIFOs and pay a higher</span></div><div class='line' id='LC857'><span class="cm">   * AVR runtime cost as toll.</span></div><div class='line' id='LC858'><span class="cm">   *</span></div><div class='line' id='LC859'><span class="cm">   * @param mode HIGH to take this unit off the SPI bus, LOW to put it on</span></div><div class='line' id='LC860'><span class="cm">   */</span></div><div class='line' id='LC861'>&nbsp;&nbsp;<span class="kt">void</span> <span class="n">csn</span><span class="p">(</span><span class="kt">bool</span> <span class="n">mode</span><span class="p">);</span></div><div class='line' id='LC862'><br></div><div class='line' id='LC863'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC864'><span class="cm">   * Set chip enable</span></div><div class='line' id='LC865'><span class="cm">   *</span></div><div class='line' id='LC866'><span class="cm">   * @param level HIGH to actively begin transmission or LOW to put in standby.  Please see data sheet</span></div><div class='line' id='LC867'><span class="cm">   * for a much more detailed description of this pin.</span></div><div class='line' id='LC868'><span class="cm">   */</span></div><div class='line' id='LC869'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">ce</span><span class="p">(</span><span class="kt">bool</span> <span class="n">level</span><span class="p">);</span></div><div class='line' id='LC870'><br></div><div class='line' id='LC871'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC872'><span class="cm">   * Read a chunk of data in from a register</span></div><div class='line' id='LC873'><span class="cm">   *</span></div><div class='line' id='LC874'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC875'><span class="cm">   * @param buf Where to put the data</span></div><div class='line' id='LC876'><span class="cm">   * @param len How many bytes of data to transfer</span></div><div class='line' id='LC877'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC878'><span class="cm">   */</span></div><div class='line' id='LC879'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">read_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC880'><br></div><div class='line' id='LC881'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC882'><span class="cm">   * Read single byte from a register</span></div><div class='line' id='LC883'><span class="cm">   *</span></div><div class='line' id='LC884'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC885'><span class="cm">   * @return Current value of register @p reg</span></div><div class='line' id='LC886'><span class="cm">   */</span></div><div class='line' id='LC887'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">read_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">);</span></div><div class='line' id='LC888'><br></div><div class='line' id='LC889'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC890'><span class="cm">   * Write a chunk of data to a register</span></div><div class='line' id='LC891'><span class="cm">   *</span></div><div class='line' id='LC892'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC893'><span class="cm">   * @param buf Where to get the data</span></div><div class='line' id='LC894'><span class="cm">   * @param len How many bytes of data to transfer</span></div><div class='line' id='LC895'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC896'><span class="cm">   */</span></div><div class='line' id='LC897'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">write_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC898'><br></div><div class='line' id='LC899'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC900'><span class="cm">   * Write a single byte to a register</span></div><div class='line' id='LC901'><span class="cm">   *</span></div><div class='line' id='LC902'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC903'><span class="cm">   * @param value The new value to write</span></div><div class='line' id='LC904'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC905'><span class="cm">   */</span></div><div class='line' id='LC906'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">write_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">value</span><span class="p">);</span></div><div class='line' id='LC907'><br></div><div class='line' id='LC908'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC909'><span class="cm">   * Write the transmit payload</span></div><div class='line' id='LC910'><span class="cm">   *</span></div><div class='line' id='LC911'><span class="cm">   * The size of data written is the fixed payload size, see getPayloadSize()</span></div><div class='line' id='LC912'><span class="cm">   *</span></div><div class='line' id='LC913'><span class="cm">   * @param buf Where to get the data</span></div><div class='line' id='LC914'><span class="cm">   * @param len Number of bytes to be sent</span></div><div class='line' id='LC915'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC916'><span class="cm">   */</span></div><div class='line' id='LC917'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">write_payload</span><span class="p">(</span><span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">writeType</span><span class="p">);</span></div><div class='line' id='LC918'><br></div><div class='line' id='LC919'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC920'><span class="cm">   * Read the receive payload</span></div><div class='line' id='LC921'><span class="cm">   *</span></div><div class='line' id='LC922'><span class="cm">   * The size of data read is the fixed payload size, see getPayloadSize()</span></div><div class='line' id='LC923'><span class="cm">   *</span></div><div class='line' id='LC924'><span class="cm">   * @param buf Where to put the data</span></div><div class='line' id='LC925'><span class="cm">   * @param len Maximum number of bytes to read</span></div><div class='line' id='LC926'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC927'><span class="cm">   */</span></div><div class='line' id='LC928'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">read_payload</span><span class="p">(</span><span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC929'><br></div><div class='line' id='LC930'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC931'><span class="cm">   * Empty the receive buffer</span></div><div class='line' id='LC932'><span class="cm">   *</span></div><div class='line' id='LC933'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC934'><span class="cm">   */</span></div><div class='line' id='LC935'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">flush_rx</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC936'><br></div><div class='line' id='LC937'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC938'><span class="cm">   * Retrieve the current status of the chip</span></div><div class='line' id='LC939'><span class="cm">   *</span></div><div class='line' id='LC940'><span class="cm">   * @return Current value of status register</span></div><div class='line' id='LC941'><span class="cm">   */</span></div><div class='line' id='LC942'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">get_status</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC943'><br></div><div class='line' id='LC944'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC945'><span class="cm">   * Decode and print the given status to stdout</span></div><div class='line' id='LC946'><span class="cm">   *</span></div><div class='line' id='LC947'><span class="cm">   * @param status Status value to print</span></div><div class='line' id='LC948'><span class="cm">   *</span></div><div class='line' id='LC949'><span class="cm">   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h</span></div><div class='line' id='LC950'><span class="cm">   */</span></div><div class='line' id='LC951'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">print_status</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">status</span><span class="p">);</span></div><div class='line' id='LC952'><br></div><div class='line' id='LC953'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC954'><span class="cm">   * Decode and print the given &#39;observe_tx&#39; value to stdout</span></div><div class='line' id='LC955'><span class="cm">   *</span></div><div class='line' id='LC956'><span class="cm">   * @param value The observe_tx value to print</span></div><div class='line' id='LC957'><span class="cm">   *</span></div><div class='line' id='LC958'><span class="cm">   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h</span></div><div class='line' id='LC959'><span class="cm">   */</span></div><div class='line' id='LC960'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">print_observe_tx</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">value</span><span class="p">);</span></div><div class='line' id='LC961'><br></div><div class='line' id='LC962'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC963'><span class="cm">   * Print the name and value of an 8-bit register to stdout</span></div><div class='line' id='LC964'><span class="cm">   *</span></div><div class='line' id='LC965'><span class="cm">   * Optionally it can print some quantity of successive</span></div><div class='line' id='LC966'><span class="cm">   * registers on the same line.  This is useful for printing a group</span></div><div class='line' id='LC967'><span class="cm">   * of related registers on one line.</span></div><div class='line' id='LC968'><span class="cm">   *</span></div><div class='line' id='LC969'><span class="cm">   * @param name Name of the register</span></div><div class='line' id='LC970'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC971'><span class="cm">   * @param qty How many successive registers to print</span></div><div class='line' id='LC972'><span class="cm">   */</span></div><div class='line' id='LC973'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">print_byte_register</span><span class="p">(</span><span class="k">const</span> <span class="kt">char</span><span class="o">*</span> <span class="n">name</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">qty</span> <span class="o">=</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC974'><br></div><div class='line' id='LC975'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC976'><span class="cm">   * Print the name and value of a 40-bit address register to stdout</span></div><div class='line' id='LC977'><span class="cm">   *</span></div><div class='line' id='LC978'><span class="cm">   * Optionally it can print some quantity of successive</span></div><div class='line' id='LC979'><span class="cm">   * registers on the same line.  This is useful for printing a group</span></div><div class='line' id='LC980'><span class="cm">   * of related registers on one line.</span></div><div class='line' id='LC981'><span class="cm">   *</span></div><div class='line' id='LC982'><span class="cm">   * @param name Name of the register</span></div><div class='line' id='LC983'><span class="cm">   * @param reg Which register. Use constants from nRF24L01.h</span></div><div class='line' id='LC984'><span class="cm">   * @param qty How many successive registers to print</span></div><div class='line' id='LC985'><span class="cm">   */</span></div><div class='line' id='LC986'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">print_address_register</span><span class="p">(</span><span class="k">const</span> <span class="kt">char</span><span class="o">*</span> <span class="n">name</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">qty</span> <span class="o">=</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC987'><br></div><div class='line' id='LC988'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC989'><span class="cm">   * Turn on or off the special features of the chip</span></div><div class='line' id='LC990'><span class="cm">   *</span></div><div class='line' id='LC991'><span class="cm">   * The chip has certain &#39;features&#39; which are only available when the &#39;features&#39;</span></div><div class='line' id='LC992'><span class="cm">   * are enabled.  See the datasheet for details.</span></div><div class='line' id='LC993'><span class="cm">   */</span></div><div class='line' id='LC994'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">toggle_features</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC995'><br></div><div class='line' id='LC996'>&nbsp;&nbsp;<span class="cm">/**</span></div><div class='line' id='LC997'><span class="cm">   * Built in spi transfer function to simplify repeating code repeating code</span></div><div class='line' id='LC998'><span class="cm">   */</span></div><div class='line' id='LC999'><br></div><div class='line' id='LC1000'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">spiTrans</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">cmd</span><span class="p">);</span></div><div class='line' id='LC1001'><span class="cp">  </span></div><div class='line' id='LC1002'><span class="cp">  #if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC1003'>	<span class="kt">void</span> <span class="nf">errNotify</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC1004'><span class="cp">  #endif</span></div><div class='line' id='LC1005'>&nbsp;&nbsp;</div><div class='line' id='LC1006'>&nbsp;&nbsp;<span class="cm">/**@}*/</span></div><div class='line' id='LC1007'><br></div><div class='line' id='LC1008'><span class="p">};</span></div><div class='line' id='LC1009'><br></div><div class='line' id='LC1010'><span class="cm">/**</span></div><div class='line' id='LC1011'><span class="cm"> * @example GettingStarted.ino</span></div><div class='line' id='LC1012'><span class="cm"> * &lt;b&gt;Updated: TMRh20 2014 &lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1013'><span class="cm"> *</span></div><div class='line' id='LC1014'><span class="cm"> * This is an example of how to use the RF24 class to communicate on a basic level.  Write this sketch to two</span></div><div class='line' id='LC1015'><span class="cm"> * different nodes. Put one of the nodes into &#39;transmit&#39; mode by connecting with the serial monitor and &lt;br&gt;</span></div><div class='line' id='LC1016'><span class="cm"> * sending a &#39;T&#39;. The ping node sends the current time to the pong node, which responds by sending the value</span></div><div class='line' id='LC1017'><span class="cm"> * back. The ping node can then see how long the whole cycle took. &lt;br&gt;</span></div><div class='line' id='LC1018'><span class="cm"> * @note For a more efficient call-response scenario see the GettingStarted_CallResponse.ino example.</span></div><div class='line' id='LC1019'><span class="cm"> * @note When switching between sketches, the radio may need to be powered down to clear settings that are not &quot;un-set&quot; otherwise</span></div><div class='line' id='LC1020'><span class="cm"> */</span></div><div class='line' id='LC1021'><br></div><div class='line' id='LC1022'><span class="cm">/**</span></div><div class='line' id='LC1023'><span class="cm"> * @example GettingStarted_CallResponse.ino</span></div><div class='line' id='LC1024'><span class="cm"> * &lt;b&gt;New: TMRh20 2014&lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1025'><span class="cm"> *</span></div><div class='line' id='LC1026'><span class="cm"> * This example continues to make use of all the normal functionality of the radios including</span></div><div class='line' id='LC1027'><span class="cm"> * the auto-ack and auto-retry features, but allows ack-payloads to be written optionlly as well. &lt;br&gt;</span></div><div class='line' id='LC1028'><span class="cm"> * This allows very fast call-response communication, with the responding radio never having to</span></div><div class='line' id='LC1029'><span class="cm"> * switch out of Primary Receiver mode to send back a payload, but having the option to switch to &lt;br&gt;</span></div><div class='line' id='LC1030'><span class="cm"> * primary transmitter if wanting to initiate communication instead of respond to a commmunication.</span></div><div class='line' id='LC1031'><span class="cm"> */</span></div><div class='line' id='LC1032'><br></div><div class='line' id='LC1033'><span class="cm">/**</span></div><div class='line' id='LC1034'><span class="cm"> * @example Transfer.ino</span></div><div class='line' id='LC1035'><span class="cm"> * &lt;b&gt;New: TMRh20 &lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1036'><span class="cm"> * This example demonstrates half-rate transfer using the FIFO buffers&lt;br&gt;</span></div><div class='line' id='LC1037'><span class="cm"> *</span></div><div class='line' id='LC1038'><span class="cm"> * It is an example of how to use the RF24 class.  Write this sketch to two</span></div><div class='line' id='LC1039'><span class="cm"> * different nodes.  Put one of the nodes into &#39;transmit&#39; mode by connecting &lt;br&gt;</span></div><div class='line' id='LC1040'><span class="cm"> * with the serial monitor and sending a &#39;T&#39;.  The data transfer will begin,</span></div><div class='line' id='LC1041'><span class="cm"> * with the receiver displaying the payload count. (32Byte Payloads) &lt;br&gt;</span></div><div class='line' id='LC1042'><span class="cm"> */</span></div><div class='line' id='LC1043'><br></div><div class='line' id='LC1044'><span class="cm">/**</span></div><div class='line' id='LC1045'><span class="cm"> * @example TransferTimeouts.ino</span></div><div class='line' id='LC1046'><span class="cm"> * &lt;b&gt;New: TMRh20 &lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1047'><span class="cm"> * This example demonstrates the use of and extended timeout period and</span></div><div class='line' id='LC1048'><span class="cm"> * auto-retries/auto-reUse to increase reliability in noisy or low signal scenarios. &lt;br&gt;</span></div><div class='line' id='LC1049'><span class="cm"> *</span></div><div class='line' id='LC1050'><span class="cm"> * Write this sketch to two different nodes.  Put one of the nodes into &#39;transmit&#39;</span></div><div class='line' id='LC1051'><span class="cm"> * mode by connecting with the serial monitor and sending a &#39;T&#39;.  The data &lt;br&gt;</span></div><div class='line' id='LC1052'><span class="cm"> * transfer will begin, with the receiver displaying the payload count and the</span></div><div class='line' id='LC1053'><span class="cm"> * data transfer rate.</span></div><div class='line' id='LC1054'><span class="cm"> */</span></div><div class='line' id='LC1055'><br></div><div class='line' id='LC1056'><span class="cm">/**</span></div><div class='line' id='LC1057'><span class="cm"> * @example starping.pde</span></div><div class='line' id='LC1058'><span class="cm"> *</span></div><div class='line' id='LC1059'><span class="cm"> * This sketch is a more complex example of using the RF24 library for Arduino.</span></div><div class='line' id='LC1060'><span class="cm"> * Deploy this on up to six nodes.  Set one as the &#39;pong receiver&#39; by tying the</span></div><div class='line' id='LC1061'><span class="cm"> * role_pin low, and the others will be &#39;ping transmit&#39; units.  The ping units</span></div><div class='line' id='LC1062'><span class="cm"> * unit will send out the value of millis() once a second.  The pong unit will</span></div><div class='line' id='LC1063'><span class="cm"> * respond back with a copy of the value.  Each ping unit can get that response</span></div><div class='line' id='LC1064'><span class="cm"> * back, and determine how long the whole cycle took.</span></div><div class='line' id='LC1065'><span class="cm"> *</span></div><div class='line' id='LC1066'><span class="cm"> * This example requires a bit more complexity to determine which unit is which.</span></div><div class='line' id='LC1067'><span class="cm"> * The pong receiver is identified by having its role_pin tied to ground.</span></div><div class='line' id='LC1068'><span class="cm"> * The ping senders are further differentiated by a byte in eeprom.</span></div><div class='line' id='LC1069'><span class="cm"> */</span></div><div class='line' id='LC1070'><br></div><div class='line' id='LC1071'><span class="cm">/**</span></div><div class='line' id='LC1072'><span class="cm"> * @example pingpair_ack.ino</span></div><div class='line' id='LC1073'><span class="cm"> * &lt;b&gt;Update: TMRh20&lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1074'><span class="cm"> * This example continues to make use of all the normal functionality of the radios including</span></div><div class='line' id='LC1075'><span class="cm"> * the auto-ack and auto-retry features, but allows ack-payloads to be written optionlly as well.&lt;br&gt;</span></div><div class='line' id='LC1076'><span class="cm"> * This allows very fast call-response communication, with the responding radio never having to</span></div><div class='line' id='LC1077'><span class="cm"> * switch out of Primary Receiver mode to send back a payload, but having the option to if wanting&lt;br&gt;</span></div><div class='line' id='LC1078'><span class="cm"> * to initiate communication instead of respond to a commmunication.</span></div><div class='line' id='LC1079'><span class="cm"> */</span></div><div class='line' id='LC1080'><br></div><div class='line' id='LC1081'><span class="cm">/**</span></div><div class='line' id='LC1082'><span class="cm"> * @example pingpair_irq.ino</span></div><div class='line' id='LC1083'><span class="cm"> * &lt;b&gt;Update: TMRh20&lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1084'><span class="cm"> * This is an example of how to user interrupts to interact with the radio, and a demonstration</span></div><div class='line' id='LC1085'><span class="cm"> * of how to use them to sleep when receiving, and not miss any payloads.&lt;br&gt;</span></div><div class='line' id='LC1086'><span class="cm"> * The pingpair_sleepy example expands on sleep functionality with a timed sleep option for the transmitter.</span></div><div class='line' id='LC1087'><span class="cm"> * Sleep functionality is built directly into my fork of the RF24Network library&lt;br&gt;</span></div><div class='line' id='LC1088'><span class="cm"> */</span></div><div class='line' id='LC1089'><br></div><div class='line' id='LC1090'><span class="cm">/**</span></div><div class='line' id='LC1091'><span class="cm"> * @example pingpair_sleepy.ino</span></div><div class='line' id='LC1092'><span class="cm"> * &lt;b&gt;Update: TMRh20&lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1093'><span class="cm"> * This is an example of how to use the RF24 class to create a battery-</span></div><div class='line' id='LC1094'><span class="cm"> * efficient system.  It is just like the GettingStarted_CallResponse example, but the&lt;br&gt;</span></div><div class='line' id='LC1095'><span class="cm"> * ping node powers down the radio and sleeps the MCU after every</span></div><div class='line' id='LC1096'><span class="cm"> * ping/pong cycle, and the receiver sleeps between payloads. &lt;br&gt;</span></div><div class='line' id='LC1097'><span class="cm"> */</span></div><div class='line' id='LC1098'><br></div><div class='line' id='LC1099'><span class="cm">/**</span></div><div class='line' id='LC1100'><span class="cm"> * @example pingpair_dyn.ino</span></div><div class='line' id='LC1101'><span class="cm"> *</span></div><div class='line' id='LC1102'><span class="cm"> * This is an example of how to use payloads of a varying (dynamic) size.</span></div><div class='line' id='LC1103'><span class="cm"> */</span></div><div class='line' id='LC1104'><br></div><div class='line' id='LC1105'><span class="cm">/**</span></div><div class='line' id='LC1106'><span class="cm"> * @example pingpair_maple.pde</span></div><div class='line' id='LC1107'><span class="cm"> *</span></div><div class='line' id='LC1108'><span class="cm"> * This is an example of how to use the RF24 class on the Maple.  For a more</span></div><div class='line' id='LC1109'><span class="cm"> * detailed explanation, see my blog post:</span></div><div class='line' id='LC1110'><span class="cm"> * &lt;a href=&quot;http://maniacbug.wordpress.com/2011/12/14/nrf24l01-running-on-maple-3/&quot;&gt;nRF24L01+ Running on Maple&lt;/a&gt;</span></div><div class='line' id='LC1111'><span class="cm"> *</span></div><div class='line' id='LC1112'><span class="cm"> * It will communicate well to an Arduino-based unit as well, so it&#39;s not for only Maple-to-Maple communication.</span></div><div class='line' id='LC1113'><span class="cm"> *</span></div><div class='line' id='LC1114'><span class="cm"> * Write this sketch to two different nodes,</span></div><div class='line' id='LC1115'><span class="cm"> * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,</span></div><div class='line' id='LC1116'><span class="cm"> * which responds by sending the value back.  The ping node can then see how long the whole cycle</span></div><div class='line' id='LC1117'><span class="cm"> * took.</span></div><div class='line' id='LC1118'><span class="cm"> */</span></div><div class='line' id='LC1119'><br></div><div class='line' id='LC1120'><span class="cm">/**</span></div><div class='line' id='LC1121'><span class="cm"> * @example nordic_fob.pde</span></div><div class='line' id='LC1122'><span class="cm"> *</span></div><div class='line' id='LC1123'><span class="cm"> * This is an example of how to use the RF24 class to receive signals from the</span></div><div class='line' id='LC1124'><span class="cm"> * Sparkfun Nordic FOB.  See http://www.sparkfun.com/products/8602 .</span></div><div class='line' id='LC1125'><span class="cm"> * Thanks to Kirk Mower for providing test hardware.</span></div><div class='line' id='LC1126'><span class="cm"> */</span></div><div class='line' id='LC1127'><br></div><div class='line' id='LC1128'><span class="cm">/**</span></div><div class='line' id='LC1129'><span class="cm"> * @example led_remote.pde</span></div><div class='line' id='LC1130'><span class="cm"> *</span></div><div class='line' id='LC1131'><span class="cm"> * This is an example of how to use the RF24 class to control a remote</span></div><div class='line' id='LC1132'><span class="cm"> * bank of LED&#39;s using buttons on a remote control.</span></div><div class='line' id='LC1133'><span class="cm"> *</span></div><div class='line' id='LC1134'><span class="cm"> * Every time the buttons change on the remote, the entire state of</span></div><div class='line' id='LC1135'><span class="cm"> * buttons is send to the led board, which displays the state.</span></div><div class='line' id='LC1136'><span class="cm"> */</span></div><div class='line' id='LC1137'><br></div><div class='line' id='LC1138'><span class="cm">/**</span></div><div class='line' id='LC1139'><span class="cm"> * @example scanner.ino</span></div><div class='line' id='LC1140'><span class="cm"> *</span></div><div class='line' id='LC1141'><span class="cm"> * Example to detect interference on the various channels available.</span></div><div class='line' id='LC1142'><span class="cm"> * This is a good diagnostic tool to check whether you&#39;re picking a</span></div><div class='line' id='LC1143'><span class="cm"> * good channel for your application.</span></div><div class='line' id='LC1144'><span class="cm"> *</span></div><div class='line' id='LC1145'><span class="cm"> * Inspired by cpixip.</span></div><div class='line' id='LC1146'><span class="cm"> * See http://arduino.cc/forum/index.php/topic,54795.0.html</span></div><div class='line' id='LC1147'><span class="cm"> */</span></div><div class='line' id='LC1148'><br></div><div class='line' id='LC1149'><span class="cm">/**</span></div><div class='line' id='LC1150'><span class="cm"> * @mainpage Optimized High Speed Driver for nRF24L01(+) 2.4GHz Wireless Transceiver</span></div><div class='line' id='LC1151'><span class="cm"> *</span></div><div class='line' id='LC1152'><span class="cm"> * @section Goals Design Goals</span></div><div class='line' id='LC1153'><span class="cm"> *</span></div><div class='line' id='LC1154'><span class="cm"> * This library fork is designed to be...</span></div><div class='line' id='LC1155'><span class="cm"> * @li More compliant with the manufacturer specified operation of the chip, while allowing advanced users</span></div><div class='line' id='LC1156'><span class="cm"> * to work outside the recommended operation.</span></div><div class='line' id='LC1157'><span class="cm"> * @li Utilize the capabilities of the radio to their full potential via Arduino</span></div><div class='line' id='LC1158'><span class="cm"> * @li More reliable, responsive and feature rich</span></div><div class='line' id='LC1159'><span class="cm"> * @li Easy for beginners to use, with well documented examples and features</span></div><div class='line' id='LC1160'><span class="cm"> * @li Consumed with a public interface that&#39;s similiar to other Arduino standard libraries</span></div><div class='line' id='LC1161'><span class="cm"> *</span></div><div class='line' id='LC1162'><span class="cm"> * @section News News</span></div><div class='line' id='LC1163'><span class="cm"> *</span></div><div class='line' id='LC1164'><span class="cm"> * &lt;b&gt;Main changes: &lt;/b&gt;&lt;br&gt;</span></div><div class='line' id='LC1165'><span class="cm"> * - The library has been tweaked to allow full use of the FIFO buffers for maximum transfer speeds</span></div><div class='line' id='LC1166'><span class="cm"> * - Changes to read() and available () functionality have increased reliability and response</span></div><div class='line' id='LC1167'><span class="cm"> * - Extended timeout periods have been added to aid in noisy or otherwise unreliable environments</span></div><div class='line' id='LC1168'><span class="cm"> * - Delays have been removed where possible to ensure maximum efficiency</span></div><div class='line' id='LC1169'><span class="cm"> * - Full Due support with extended SPI functions</span></div><div class='line' id='LC1170'><span class="cm"> * - ATTiny now supported.</span></div><div class='line' id='LC1171'><span class="cm"> * - Raspberry Pi now supported</span></div><div class='line' id='LC1172'><span class="cm"> * - More! See the links below and class documentation for more info.</span></div><div class='line' id='LC1173'><span class="cm"> *</span></div><div class='line' id='LC1174'><span class="cm"> * If issues are discovered with the documentation, please report them &lt;a href=&quot;https://github.com/TMRh20/tmrh20.github.io/issues&quot;&gt; here&lt;/a&gt;</span></div><div class='line' id='LC1175'><span class="cm"> * @section Useful Useful References</span></div><div class='line' id='LC1176'><span class="cm"> *</span></div><div class='line' id='LC1177'><span class="cm"> * Please refer to:</span></div><div class='line' id='LC1178'><span class="cm"> *</span></div><div class='line' id='LC1179'><span class="cm"> * @li &lt;a href=&quot;http://tmrh20.github.io/&quot;&gt;Documentation Main Page&lt;/a&gt;</span></div><div class='line' id='LC1180'><span class="cm"> * @li &lt;a href=&quot;http://tmrh20.github.io/RF24/classRF24.html&quot;&gt;RF24 Class Documentation&lt;/a&gt;</span></div><div class='line' id='LC1181'><span class="cm"> * @li &lt;a href=&quot;https://github.com/tmrh20/RF24/&quot;&gt;Source Code&lt;/a&gt;</span></div><div class='line' id='LC1182'><span class="cm"> * @li &lt;a href=&quot;https://github.com/TMRh20/RF24/archive/master.zip&quot;&gt;Download&lt;/a&gt;</span></div><div class='line' id='LC1183'><span class="cm"> * @li &lt;a href=&quot;http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf&quot;&gt;Chip Datasheet&lt;/a&gt;</span></div><div class='line' id='LC1184'><span class="cm"> * @li &lt;a href=&quot;https://github.com/maniacbug/RF24&quot;&gt;Original Library&lt;/a&gt;</span></div><div class='line' id='LC1185'><span class="cm"> *</span></div><div class='line' id='LC1186'><span class="cm"> * This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or</span></div><div class='line' id='LC1187'><span class="cm"> * the SPI hardware will go into &#39;slave&#39; mode.</span></div><div class='line' id='LC1188'><span class="cm"> *</span></div><div class='line' id='LC1189'><span class="cm"> * @section Board_Support Board Support</span></div><div class='line' id='LC1190'><span class="cm"> *</span></div><div class='line' id='LC1191'><span class="cm"> * Most standard Arduino based boards are supported:</span></div><div class='line' id='LC1192'><span class="cm"> * - ATMega 328 based boards (Uno, Nano, etc)</span></div><div class='line' id='LC1193'><span class="cm"> * - Mega Boards (1280, 2560, etc)</span></div><div class='line' id='LC1194'><span class="cm"> * - Arduino Due: Must use one of the hardware SS/CSN pins as extended SPI methods are used.</span></div><div class='line' id='LC1195'><span class="cm"> *  Initial Due support taken from https://github.com/mcrosson/RF24/tree/due</span></div><div class='line' id='LC1196'><span class="cm"> * - ATTiny board support added from https://github.com/jscrane/RF24</span></div><div class='line' id='LC1197'><span class="cm"> * Note: ATTiny support is built into the library. Do not include SPI.h. &lt;br&gt;</span></div><div class='line' id='LC1198'><span class="cm"> * ATTiny 85: D0(pin 5): MISO, D1(pin6) MOSI, D2(pin7) SCK, D3(pin2):CSN/SS, D4(pin3): CE &lt;br&gt;</span></div><div class='line' id='LC1199'><span class="cm"> * ATTiny 84: PA6:MISO, PA5:MOSI, PA4:SCK, PA7:CSN/SS,  CE as desired &lt;br&gt;</span></div><div class='line' id='LC1200'><span class="cm"> * See https://github.com/TCWORLD/ATTinyCore/tree/master/PCREL%20Patch%20for%20GCC for ATTiny patch</span></div><div class='line' id='LC1201'><span class="cm"> * - Raspberry Pi Support: See the readme at https://github.com/TMRh20/RF24/tree/master/RPi</span></div><div class='line' id='LC1202'><span class="cm"> *</span></div><div class='line' id='LC1203'><span class="cm"> * @section More More Information</span></div><div class='line' id='LC1204'><span class="cm"> *</span></div><div class='line' id='LC1205'><span class="cm"> * @section Info and Projects</span></div><div class='line' id='LC1206'><span class="cm"> *</span></div><div class='line' id='LC1207'><span class="cm"> * @li Project blog:</span></div><div class='line' id='LC1208'><span class="cm"> * @li &lt;a href=&quot;http://TMRh20.blogspot.com&quot;&gt; TMRh20.blogspot.com &lt;/a&gt;</span></div><div class='line' id='LC1209'><span class="cm"> * @li &lt;a href=&quot;http://tmrh20.github.io/RF24Audio/&quot;&gt; RF24 Wireless Audio Library &lt;/a&gt;</span></div><div class='line' id='LC1210'><span class="cm"> * @li &lt;a href=&quot;https://github.com/TMRh20/RF24Network&quot;&gt; Optimized RF24 Network Layer &lt;/a&gt;</span></div><div class='line' id='LC1211'><span class="cm"> * @li &lt;a href=&quot;https://github.com/maniacbug/RF24&quot;&gt; ManiacBug on GitHub (Original Library Author)&lt;/a&gt;</span></div><div class='line' id='LC1212'><span class="cm"> */</span></div><div class='line' id='LC1213'><br></div><div class='line' id='LC1214'><span class="cp">#endif </span><span class="c1">// __RF24_H__</span></div><div class='line' id='LC1215'><br></div><div class='line' id='LC1216'><br></div></pre></div></td>
         </tr>
       </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/" aria-label="Homepage">
      <span class="mega-octicon octicon-mark-github" title="GitHub"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2014 <span title="0.04170s from github-fe129-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-suggester-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="fullscreen-contents js-fullscreen-contents js-suggester-field" placeholder=""></textarea>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped tooltipped-w" aria-label="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped tooltipped-w"
      aria-label="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-x close js-ajax-error-dismiss" aria-label="Dismiss error"></a>
      Something went wrong with that request. Please try again.
    </div>


      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/frameworks-8c6e10f6700610e693b29e274318b3714523ca3e.js" type="text/javascript"></script>
      <script async="async" crossorigin="anonymous" src="https://assets-cdn.github.com/assets/github-8cb2cf90ade4ed9e5f018ba0309e9b3d0bf0c6db.js" type="text/javascript"></script>
      
      
        <script async src="https://www.google-analytics.com/analytics.js"></script>
  </body>
</html>

