




<!DOCTYPE html>
<html class="   ">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    
    
    <title>RF24/RF24.cpp at master · TMRh20/RF24</title>
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

    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="AF8EE9B5:0445:B3BFFFF:53DF2AC4" name="octolytics-dimension-request_id" /><meta content="539857" name="octolytics-actor-id" /><meta content="stanleyseow" name="octolytics-actor-login" /><meta content="a8e79e6be21d3d96d6758fbbbd41706d09d3d9abe9313e40b002417705fcb09e" name="octolytics-actor-hash" />
    

    
    
    <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico">


    <meta content="authenticity_token" name="csrf-param" />
<meta content="20APMz+4E4TyPKMUtG2oGXlWlVopukiHsR/EDdUo61riO7ZO4aHu0xpxVMJGk/bBBA/4j0lhOO+/NFTO8c/4ww==" name="csrf-token" />

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
    <form accept-charset="UTF-8" action="/logout" class="logout-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="7s2+XhsEFy2V9ca7Ds9uXwPMYjL7HgRgUGADSNOXgDifTseQ1xaaGMp/dzNKDA/X+o/s8qzm80yGSC1TH1eRSQ==" /></div>
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
      <form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="iDoXdq2Fsd6eaCW6uXHQdYEc9GDT7NC2XHU7KJaMQSRuU+4DlkmI4u57bU7aWAJLkVjr9JorvRi/f9M0Wr3YkQ==" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="17856505" />

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

    <form accept-charset="UTF-8" action="/TMRh20/RF24/unstar" class="js-toggler-form starred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="nWk6Y9M+ZPk08PcpCFvgJfkcGnCFjWA2g9agPITXbyceBzBGpW/plSgheMO4k1AFPmGpMuW8GMbGahIUrPM+dA==" /></div>
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
    <form accept-charset="UTF-8" action="/TMRh20/RF24/star" class="js-toggler-form unstarred" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="K8E6PHld1pVEEAm5amcj4atOeSx1o9V5RaOcG0wr9oQ1AWqarJaouCDi4olGMByD9NY3FGxVkW0T67sMtP460A==" /></div>
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
          


<a href="/TMRh20/RF24/blob/327f0609cf7b52b70accccc175b5809dd5074704/RF24.cpp" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:bfabb264c26ad75ded50e2ecef5083cf -->

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
              <a href="/TMRh20/RF24/blob/arduino-1.0/RF24.cpp"
                 data-name="arduino-1.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="arduino-1.0">arduino-1.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/gh-pages/RF24.cpp"
                 data-name="gh-pages"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="gh-pages">gh-pages</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/interrupts/RF24.cpp"
                 data-name="interrupts"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="interrupts">interrupts</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/master/RF24.cpp"
                 data-name="master"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="master">master</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/p_enable/RF24.cpp"
                 data-name="p_enable"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="p_enable">p_enable</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/TMRh20/RF24/blob/write_bug/RF24.cpp"
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
          data-clipboard-text="RF24.cpp"
          aria-label="Copy to clipboard"
          data-copied-hint="Copied!">
      <span class="octicon octicon-clippy"></span>
    </button>
  </div>

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/TMRh20/RF24" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">RF24</span></a></span></span><span class="separator"> / </span><strong class="final-path">RF24.cpp</strong>
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
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>5</strong>  contributors</a></p>
          <a class="avatar tooltipped tooltipped-s" aria-label="maniacbug" href="/TMRh20/RF24/commits/master/RF24.cpp?author=maniacbug"><img alt="maniacbug" data-user="636684" height="20" src="https://avatars0.githubusercontent.com/u/636684?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="TMRh20" href="/TMRh20/RF24/commits/master/RF24.cpp?author=TMRh20"><img alt="TMRh20" data-user="2610460" height="20" src="https://avatars3.githubusercontent.com/u/2610460?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="gcopeland" href="/TMRh20/RF24/commits/master/RF24.cpp?author=gcopeland"><img alt="gcopeland" data-user="310269" height="20" src="https://avatars2.githubusercontent.com/u/310269?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="zephyrr" href="/TMRh20/RF24/commits/master/RF24.cpp?author=zephyrr"><img alt="zephyrr" data-user="4857690" height="20" src="https://avatars0.githubusercontent.com/u/4857690?v=1&amp;s=40" width="20" /></a>
    <a class="avatar tooltipped tooltipped-s" aria-label="a-lurker" href="/TMRh20/RF24/commits/master/RF24.cpp?author=a-lurker"><img alt="a-lurker" data-user="7496794" height="20" src="https://avatars3.githubusercontent.com/u/7496794?v=1&amp;s=40" width="20" /></a>


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
            <img alt="zephyrr" data-user="4857690" height="24" src="https://avatars2.githubusercontent.com/u/4857690?v=1&amp;s=48" width="24" />
            <a href="/zephyrr">zephyrr</a>
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
          <span>1320 lines (1021 sloc)</span>
          <span class="meta-divider"></span>
        <span>36.62 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
          <a href="/TMRh20/RF24/raw/master/RF24.cpp" class="minibutton " id="raw-url">Raw</a>
            <a href="/TMRh20/RF24/blame/master/RF24.cpp" class="minibutton js-update-url-with-hash">Blame</a>
          <a href="/TMRh20/RF24/commits/master/RF24.cpp" class="minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->

          <a class="octicon-button tooltipped tooltipped-nw js-conduit-openfile-check"
             href="http://mac.github.com"
             data-url="github-mac://openRepo/https://github.com/TMRh20/RF24?branch=master&amp;filepath=RF24.cpp"
             aria-label="Open this file in GitHub for Mac"
             data-failed-title="Your version of GitHub for Mac is too old to open this file. Try checking for updates.">
              <span class="octicon octicon-device-desktop"></span>
          </a>

              <a class="octicon-button tooltipped tooltipped-n js-update-url-with-hash"
                 aria-label="Clicking this button will fork this project so you can edit the file"
                 href="/TMRh20/RF24/edit/master/RF24.cpp"
                 data-method="post" rel="nofollow"><span class="octicon octicon-pencil"></span></a>

            <a class="octicon-button danger tooltipped tooltipped-s"
               href="/TMRh20/RF24/delete/master/RF24.cpp"
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
<span id="L1217" rel="#L1217">1217</span>
<span id="L1218" rel="#L1218">1218</span>
<span id="L1219" rel="#L1219">1219</span>
<span id="L1220" rel="#L1220">1220</span>
<span id="L1221" rel="#L1221">1221</span>
<span id="L1222" rel="#L1222">1222</span>
<span id="L1223" rel="#L1223">1223</span>
<span id="L1224" rel="#L1224">1224</span>
<span id="L1225" rel="#L1225">1225</span>
<span id="L1226" rel="#L1226">1226</span>
<span id="L1227" rel="#L1227">1227</span>
<span id="L1228" rel="#L1228">1228</span>
<span id="L1229" rel="#L1229">1229</span>
<span id="L1230" rel="#L1230">1230</span>
<span id="L1231" rel="#L1231">1231</span>
<span id="L1232" rel="#L1232">1232</span>
<span id="L1233" rel="#L1233">1233</span>
<span id="L1234" rel="#L1234">1234</span>
<span id="L1235" rel="#L1235">1235</span>
<span id="L1236" rel="#L1236">1236</span>
<span id="L1237" rel="#L1237">1237</span>
<span id="L1238" rel="#L1238">1238</span>
<span id="L1239" rel="#L1239">1239</span>
<span id="L1240" rel="#L1240">1240</span>
<span id="L1241" rel="#L1241">1241</span>
<span id="L1242" rel="#L1242">1242</span>
<span id="L1243" rel="#L1243">1243</span>
<span id="L1244" rel="#L1244">1244</span>
<span id="L1245" rel="#L1245">1245</span>
<span id="L1246" rel="#L1246">1246</span>
<span id="L1247" rel="#L1247">1247</span>
<span id="L1248" rel="#L1248">1248</span>
<span id="L1249" rel="#L1249">1249</span>
<span id="L1250" rel="#L1250">1250</span>
<span id="L1251" rel="#L1251">1251</span>
<span id="L1252" rel="#L1252">1252</span>
<span id="L1253" rel="#L1253">1253</span>
<span id="L1254" rel="#L1254">1254</span>
<span id="L1255" rel="#L1255">1255</span>
<span id="L1256" rel="#L1256">1256</span>
<span id="L1257" rel="#L1257">1257</span>
<span id="L1258" rel="#L1258">1258</span>
<span id="L1259" rel="#L1259">1259</span>
<span id="L1260" rel="#L1260">1260</span>
<span id="L1261" rel="#L1261">1261</span>
<span id="L1262" rel="#L1262">1262</span>
<span id="L1263" rel="#L1263">1263</span>
<span id="L1264" rel="#L1264">1264</span>
<span id="L1265" rel="#L1265">1265</span>
<span id="L1266" rel="#L1266">1266</span>
<span id="L1267" rel="#L1267">1267</span>
<span id="L1268" rel="#L1268">1268</span>
<span id="L1269" rel="#L1269">1269</span>
<span id="L1270" rel="#L1270">1270</span>
<span id="L1271" rel="#L1271">1271</span>
<span id="L1272" rel="#L1272">1272</span>
<span id="L1273" rel="#L1273">1273</span>
<span id="L1274" rel="#L1274">1274</span>
<span id="L1275" rel="#L1275">1275</span>
<span id="L1276" rel="#L1276">1276</span>
<span id="L1277" rel="#L1277">1277</span>
<span id="L1278" rel="#L1278">1278</span>
<span id="L1279" rel="#L1279">1279</span>
<span id="L1280" rel="#L1280">1280</span>
<span id="L1281" rel="#L1281">1281</span>
<span id="L1282" rel="#L1282">1282</span>
<span id="L1283" rel="#L1283">1283</span>
<span id="L1284" rel="#L1284">1284</span>
<span id="L1285" rel="#L1285">1285</span>
<span id="L1286" rel="#L1286">1286</span>
<span id="L1287" rel="#L1287">1287</span>
<span id="L1288" rel="#L1288">1288</span>
<span id="L1289" rel="#L1289">1289</span>
<span id="L1290" rel="#L1290">1290</span>
<span id="L1291" rel="#L1291">1291</span>
<span id="L1292" rel="#L1292">1292</span>
<span id="L1293" rel="#L1293">1293</span>
<span id="L1294" rel="#L1294">1294</span>
<span id="L1295" rel="#L1295">1295</span>
<span id="L1296" rel="#L1296">1296</span>
<span id="L1297" rel="#L1297">1297</span>
<span id="L1298" rel="#L1298">1298</span>
<span id="L1299" rel="#L1299">1299</span>
<span id="L1300" rel="#L1300">1300</span>
<span id="L1301" rel="#L1301">1301</span>
<span id="L1302" rel="#L1302">1302</span>
<span id="L1303" rel="#L1303">1303</span>
<span id="L1304" rel="#L1304">1304</span>
<span id="L1305" rel="#L1305">1305</span>
<span id="L1306" rel="#L1306">1306</span>
<span id="L1307" rel="#L1307">1307</span>
<span id="L1308" rel="#L1308">1308</span>
<span id="L1309" rel="#L1309">1309</span>
<span id="L1310" rel="#L1310">1310</span>
<span id="L1311" rel="#L1311">1311</span>
<span id="L1312" rel="#L1312">1312</span>
<span id="L1313" rel="#L1313">1313</span>
<span id="L1314" rel="#L1314">1314</span>
<span id="L1315" rel="#L1315">1315</span>
<span id="L1316" rel="#L1316">1316</span>
<span id="L1317" rel="#L1317">1317</span>
<span id="L1318" rel="#L1318">1318</span>
<span id="L1319" rel="#L1319">1319</span>

           </td>
           <td class="blob-line-code"><div class="code-body highlight"><pre><div class='line' id='LC1'><span class="cm">/*</span></div><div class='line' id='LC2'><span class="cm"> Copyright (C) 2011 J. Coliz &lt;maniacbug@ymail.com&gt;</span></div><div class='line' id='LC3'><br></div><div class='line' id='LC4'><span class="cm"> This program is free software; you can redistribute it and/or</span></div><div class='line' id='LC5'><span class="cm"> modify it under the terms of the GNU General Public License</span></div><div class='line' id='LC6'><span class="cm"> version 2 as published by the Free Software Foundation.</span></div><div class='line' id='LC7'><span class="cm"> */</span></div><div class='line' id='LC8'><br></div><div class='line' id='LC9'><span class="cp">#include &quot;nRF24L01.h&quot;</span></div><div class='line' id='LC10'><span class="cp">#include &quot;RF24_config.h&quot;</span></div><div class='line' id='LC11'><span class="cp">#include &quot;RF24.h&quot;</span></div><div class='line' id='LC12'><br></div><div class='line' id='LC13'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC14'><br></div><div class='line' id='LC15'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">csn</span><span class="p">(</span><span class="kt">bool</span> <span class="n">mode</span><span class="p">)</span></div><div class='line' id='LC16'><span class="p">{</span></div><div class='line' id='LC17'>&nbsp;&nbsp;<span class="c1">// Minimum ideal SPI bus speed is 2x data rate</span></div><div class='line' id='LC18'>&nbsp;&nbsp;<span class="c1">// If we assume 2Mbs data rate and 16Mhz clock, a</span></div><div class='line' id='LC19'>&nbsp;&nbsp;<span class="c1">// divider of 4 is the minimum we want.</span></div><div class='line' id='LC20'>&nbsp;&nbsp;<span class="c1">// CLK:BUS 8Mhz:2Mhz, 16Mhz:4Mhz, or 20Mhz:5Mhz</span></div><div class='line' id='LC21'><span class="cp">#ifdef ARDUINO</span></div><div class='line' id='LC22'><span class="cp">	#if  ( !defined( __AVR_ATtiny85__ ) &amp;&amp; !defined( __AVR_ATtiny84__) &amp;&amp; !defined (__arm__)  ) || defined (CORE_TEENSY)</span></div><div class='line' id='LC23'>&nbsp;			<span class="n">SPI</span><span class="p">.</span><span class="n">setBitOrder</span><span class="p">(</span><span class="n">MSBFIRST</span><span class="p">);</span></div><div class='line' id='LC24'>&nbsp;&nbsp;			<span class="n">SPI</span><span class="p">.</span><span class="n">setDataMode</span><span class="p">(</span><span class="n">SPI_MODE0</span><span class="p">);</span></div><div class='line' id='LC25'>			<span class="n">SPI</span><span class="p">.</span><span class="n">setClockDivider</span><span class="p">(</span><span class="n">SPI_CLOCK_DIV2</span><span class="p">);</span></div><div class='line' id='LC26'><span class="cp">	#endif</span></div><div class='line' id='LC27'><span class="cp">#endif</span></div><div class='line' id='LC28'><br></div><div class='line' id='LC29'><span class="cp">#if !defined  (__arm__) || defined (CORE_TEENSY)</span></div><div class='line' id='LC30'>	<span class="n">digitalWrite</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="n">mode</span><span class="p">);</span></div><div class='line' id='LC31'><span class="cp">#endif</span></div><div class='line' id='LC32'><br></div><div class='line' id='LC33'><span class="p">}</span></div><div class='line' id='LC34'><br></div><div class='line' id='LC35'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC36'><br></div><div class='line' id='LC37'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">ce</span><span class="p">(</span><span class="kt">bool</span> <span class="n">level</span><span class="p">)</span></div><div class='line' id='LC38'><span class="p">{</span></div><div class='line' id='LC39'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">ce_pin</span><span class="p">,</span><span class="n">level</span><span class="p">);</span></div><div class='line' id='LC40'><span class="p">}</span></div><div class='line' id='LC41'><br></div><div class='line' id='LC42'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC43'><br></div><div class='line' id='LC44'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">read_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC45'><span class="p">{</span></div><div class='line' id='LC46'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC47'><br></div><div class='line' id='LC48'><span class="cp">#if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC49'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">R_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">),</span> <span class="n">SPI_CONTINUE</span> <span class="p">);</span></div><div class='line' id='LC50'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">len</span><span class="o">--</span> <span class="o">&gt;</span> <span class="mi">1</span> <span class="p">){</span></div><div class='line' id='LC51'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">buf</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xff</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC52'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC53'>&nbsp;&nbsp;<span class="o">*</span><span class="n">buf</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC54'><br></div><div class='line' id='LC55'><span class="cp">#else</span></div><div class='line' id='LC56'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC57'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">R_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC58'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">len</span><span class="o">--</span> <span class="p">){</span></div><div class='line' id='LC59'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">buf</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC60'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC61'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC62'><br></div><div class='line' id='LC63'><span class="cp">#endif</span></div><div class='line' id='LC64'><br></div><div class='line' id='LC65'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC66'><span class="p">}</span></div><div class='line' id='LC67'><br></div><div class='line' id='LC68'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC69'><br></div><div class='line' id='LC70'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">read_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">)</span></div><div class='line' id='LC71'><span class="p">{</span></div><div class='line' id='LC72'><br></div><div class='line' id='LC73'><span class="cp">  #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC74'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">R_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">)</span> <span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC75'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">result</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC76'><span class="cp">  #else</span></div><div class='line' id='LC77'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC78'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">R_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC79'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">result</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC80'><br></div><div class='line' id='LC81'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC82'><span class="cp">  #endif</span></div><div class='line' id='LC83'><br></div><div class='line' id='LC84'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">result</span><span class="p">;</span></div><div class='line' id='LC85'><span class="p">}</span></div><div class='line' id='LC86'><br></div><div class='line' id='LC87'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC88'><br></div><div class='line' id='LC89'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">write_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC90'><span class="p">{</span></div><div class='line' id='LC91'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC92'><br></div><div class='line' id='LC93'><span class="cp">  #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC94'>&nbsp;&nbsp;	<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">W_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">),</span> <span class="n">SPI_CONTINUE</span> <span class="p">);</span></div><div class='line' id='LC95'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="o">--</span><span class="n">len</span><span class="p">){</span></div><div class='line' id='LC96'>&nbsp;&nbsp;&nbsp;&nbsp;	<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">buf</span><span class="o">++</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC97'>	<span class="p">}</span></div><div class='line' id='LC98'>	<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">buf</span><span class="o">++</span><span class="p">);</span></div><div class='line' id='LC99'><span class="cp">  #else</span></div><div class='line' id='LC100'><br></div><div class='line' id='LC101'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC102'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">W_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC103'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">len</span><span class="o">--</span> <span class="p">)</span></div><div class='line' id='LC104'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="o">*</span><span class="n">buf</span><span class="o">++</span><span class="p">);</span></div><div class='line' id='LC105'><br></div><div class='line' id='LC106'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC107'><br></div><div class='line' id='LC108'><span class="cp">  #endif</span></div><div class='line' id='LC109'><br></div><div class='line' id='LC110'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC111'><span class="p">}</span></div><div class='line' id='LC112'><br></div><div class='line' id='LC113'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC114'><br></div><div class='line' id='LC115'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">write_register</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">value</span><span class="p">)</span></div><div class='line' id='LC116'><span class="p">{</span></div><div class='line' id='LC117'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC118'><br></div><div class='line' id='LC119'>&nbsp;&nbsp;<span class="n">IF_SERIAL_DEBUG</span><span class="p">(</span><span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;write_register(%02x,%02x)</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">reg</span><span class="p">,</span><span class="n">value</span><span class="p">));</span></div><div class='line' id='LC120'><br></div><div class='line' id='LC121'><span class="cp">  #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC122'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">W_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">),</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC123'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="n">value</span><span class="p">);</span></div><div class='line' id='LC124'><span class="cp">  #else</span></div><div class='line' id='LC125'><br></div><div class='line' id='LC126'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC127'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">W_REGISTER</span> <span class="o">|</span> <span class="p">(</span> <span class="n">REGISTER_MASK</span> <span class="o">&amp;</span> <span class="n">reg</span> <span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC128'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">value</span><span class="p">);</span></div><div class='line' id='LC129'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC130'><br></div><div class='line' id='LC131'><span class="cp">  #endif</span></div><div class='line' id='LC132'><br></div><div class='line' id='LC133'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC134'><span class="p">}</span></div><div class='line' id='LC135'><br></div><div class='line' id='LC136'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC137'><br></div><div class='line' id='LC138'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">write_payload</span><span class="p">(</span><span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">data_len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">writeType</span><span class="p">)</span></div><div class='line' id='LC139'><span class="p">{</span></div><div class='line' id='LC140'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC141'>&nbsp;&nbsp;<span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">current</span> <span class="o">=</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="n">buf</span><span class="p">);</span></div><div class='line' id='LC142'><br></div><div class='line' id='LC143'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">data_len</span> <span class="o">&gt;</span> <span class="mi">32</span><span class="p">)</span> <span class="n">data_len</span> <span class="o">=</span> <span class="mi">32</span><span class="p">;</span></div><div class='line' id='LC144'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">blank_len</span> <span class="o">=</span> <span class="n">dynamic_payloads_enabled</span> <span class="o">?</span> <span class="mi">0</span> <span class="o">:</span> <span class="mi">32</span> <span class="o">-</span> <span class="n">data_len</span><span class="p">;</span></div><div class='line' id='LC145'><br></div><div class='line' id='LC146'>&nbsp;&nbsp;<span class="c1">//printf(&quot;[Writing %u bytes %u blanks]&quot;,data_len,blank_len);</span></div><div class='line' id='LC147'><br></div><div class='line' id='LC148'><span class="cp"> #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC149'><br></div><div class='line' id='LC150'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">writeType</span> <span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC151'><br></div><div class='line' id='LC152'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">blank_len</span><span class="p">){</span></div><div class='line' id='LC153'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span><span class="p">){</span></div><div class='line' id='LC154'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC155'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC156'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="o">--</span><span class="n">blank_len</span> <span class="p">){</span></div><div class='line' id='LC157'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mi">0</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC158'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC159'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC160'>&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC161'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span><span class="p">(</span> <span class="o">--</span><span class="n">data_len</span> <span class="p">){</span></div><div class='line' id='LC162'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC163'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC164'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">current</span><span class="p">);</span></div><div class='line' id='LC165'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC166'><br></div><div class='line' id='LC167'><span class="cp">  #else</span></div><div class='line' id='LC168'><br></div><div class='line' id='LC169'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC170'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">writeType</span> <span class="p">);</span></div><div class='line' id='LC171'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC172'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">);</span></div><div class='line' id='LC173'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC174'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">blank_len</span><span class="o">--</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC175'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC176'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC177'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC178'><br></div><div class='line' id='LC179'><span class="cp">  #endif</span></div><div class='line' id='LC180'><br></div><div class='line' id='LC181'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC182'><span class="p">}</span></div><div class='line' id='LC183'><br></div><div class='line' id='LC184'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC185'><br></div><div class='line' id='LC186'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">read_payload</span><span class="p">(</span><span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">data_len</span><span class="p">)</span></div><div class='line' id='LC187'><span class="p">{</span></div><div class='line' id='LC188'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC189'>&nbsp;&nbsp;<span class="kt">uint8_t</span><span class="o">*</span> <span class="n">current</span> <span class="o">=</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="n">buf</span><span class="p">);</span></div><div class='line' id='LC190'><br></div><div class='line' id='LC191'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">data_len</span> <span class="o">&gt;</span> <span class="n">payload_size</span><span class="p">)</span> <span class="n">data_len</span> <span class="o">=</span> <span class="n">payload_size</span><span class="p">;</span></div><div class='line' id='LC192'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">blank_len</span> <span class="o">=</span> <span class="n">dynamic_payloads_enabled</span> <span class="o">?</span> <span class="mi">0</span> <span class="o">:</span> <span class="mi">32</span> <span class="o">-</span> <span class="n">data_len</span><span class="p">;</span></div><div class='line' id='LC193'><br></div><div class='line' id='LC194'>&nbsp;&nbsp;<span class="c1">//printf(&quot;[Reading %u bytes %u blanks]&quot;,data_len,blank_len);</span></div><div class='line' id='LC195'><br></div><div class='line' id='LC196'><br></div><div class='line' id='LC197'><span class="cp">  #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC198'><br></div><div class='line' id='LC199'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">R_RX_PAYLOAD</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span> <span class="p">);</span></div><div class='line' id='LC200'><br></div><div class='line' id='LC201'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">blank_len</span> <span class="p">){</span></div><div class='line' id='LC202'>	<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span> <span class="p">){</span></div><div class='line' id='LC203'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">current</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xFF</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC204'>	<span class="p">}</span></div><div class='line' id='LC205'><br></div><div class='line' id='LC206'>	<span class="k">while</span> <span class="p">(</span> <span class="o">--</span><span class="n">blank_len</span> <span class="p">){</span></div><div class='line' id='LC207'>	  <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xFF</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC208'>	<span class="p">}</span></div><div class='line' id='LC209'>	<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xFF</span><span class="p">);</span></div><div class='line' id='LC210'>&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC211'>	<span class="k">while</span> <span class="p">(</span> <span class="o">--</span><span class="n">data_len</span> <span class="p">){</span></div><div class='line' id='LC212'>	  <span class="o">*</span><span class="n">current</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xFF</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC213'>	<span class="p">}</span></div><div class='line' id='LC214'>	<span class="o">*</span><span class="n">current</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xFF</span><span class="p">);</span></div><div class='line' id='LC215'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC216'><br></div><div class='line' id='LC217'><span class="cp">  #else</span></div><div class='line' id='LC218'><br></div><div class='line' id='LC219'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC220'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">R_RX_PAYLOAD</span> <span class="p">);</span></div><div class='line' id='LC221'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC222'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">current</span><span class="o">++</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mh">0xFF</span><span class="p">);</span></div><div class='line' id='LC223'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC224'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">blank_len</span><span class="o">--</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC225'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC226'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC227'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC228'><br></div><div class='line' id='LC229'><span class="cp">  #endif</span></div><div class='line' id='LC230'><br></div><div class='line' id='LC231'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC232'><span class="p">}</span></div><div class='line' id='LC233'><br></div><div class='line' id='LC234'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC235'><br></div><div class='line' id='LC236'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">flush_rx</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC237'><span class="p">{</span></div><div class='line' id='LC238'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">spiTrans</span><span class="p">(</span> <span class="n">FLUSH_RX</span> <span class="p">);</span></div><div class='line' id='LC239'><span class="p">}</span></div><div class='line' id='LC240'><br></div><div class='line' id='LC241'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC242'><br></div><div class='line' id='LC243'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">flush_tx</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC244'><span class="p">{</span></div><div class='line' id='LC245'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">spiTrans</span><span class="p">(</span> <span class="n">FLUSH_TX</span> <span class="p">);</span></div><div class='line' id='LC246'><span class="p">}</span></div><div class='line' id='LC247'><br></div><div class='line' id='LC248'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC249'><br></div><div class='line' id='LC250'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">spiTrans</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">cmd</span><span class="p">){</span></div><div class='line' id='LC251'><br></div><div class='line' id='LC252'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC253'><span class="cp">  #if defined (__arm__) &amp;&amp; !defined ( CORE_TEENSY )</span></div><div class='line' id='LC254'>	<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">cmd</span> <span class="p">);</span></div><div class='line' id='LC255'><span class="cp">  #else</span></div><div class='line' id='LC256'><br></div><div class='line' id='LC257'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC258'>&nbsp;&nbsp;<span class="n">status</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">cmd</span> <span class="p">);</span></div><div class='line' id='LC259'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC260'><span class="cp">  #endif</span></div><div class='line' id='LC261'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">status</span><span class="p">;</span></div><div class='line' id='LC262'><br></div><div class='line' id='LC263'><span class="p">}</span></div><div class='line' id='LC264'><br></div><div class='line' id='LC265'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC266'><br></div><div class='line' id='LC267'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">get_status</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC268'><span class="p">{</span></div><div class='line' id='LC269'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">spiTrans</span><span class="p">(</span><span class="n">NOP</span><span class="p">);</span></div><div class='line' id='LC270'><span class="p">}</span></div><div class='line' id='LC271'><br></div><div class='line' id='LC272'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC273'><br></div><div class='line' id='LC274'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">print_status</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">status</span><span class="p">)</span></div><div class='line' id='LC275'><span class="p">{</span></div><div class='line' id='LC276'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;STATUS</span><span class="se">\t\t</span><span class="s"> = 0x%02x RX_DR=%x TX_DS=%x MAX_RT=%x RX_P_NO=%x TX_FULL=%x</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span></div><div class='line' id='LC277'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">status</span><span class="p">,</span></div><div class='line' id='LC278'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">))</span><span class="o">?</span><span class="mi">1</span><span class="o">:</span><span class="mi">0</span><span class="p">,</span></div><div class='line' id='LC279'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">))</span><span class="o">?</span><span class="mi">1</span><span class="o">:</span><span class="mi">0</span><span class="p">,</span></div><div class='line' id='LC280'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">))</span><span class="o">?</span><span class="mi">1</span><span class="o">:</span><span class="mi">0</span><span class="p">,</span></div><div class='line' id='LC281'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">((</span><span class="n">status</span> <span class="o">&gt;&gt;</span> <span class="n">RX_P_NO</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">B111</span><span class="p">),</span></div><div class='line' id='LC282'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_FULL</span><span class="p">))</span><span class="o">?</span><span class="mi">1</span><span class="o">:</span><span class="mi">0</span></div><div class='line' id='LC283'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">);</span></div><div class='line' id='LC284'><span class="p">}</span></div><div class='line' id='LC285'><br></div><div class='line' id='LC286'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC287'><br></div><div class='line' id='LC288'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">print_observe_tx</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">value</span><span class="p">)</span></div><div class='line' id='LC289'><span class="p">{</span></div><div class='line' id='LC290'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;OBSERVE_TX=%02x: POLS_CNT=%x ARC_CNT=%x</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span></div><div class='line' id='LC291'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">value</span><span class="p">,</span></div><div class='line' id='LC292'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">value</span> <span class="o">&gt;&gt;</span> <span class="n">PLOS_CNT</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">B1111</span><span class="p">,</span></div><div class='line' id='LC293'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">value</span> <span class="o">&gt;&gt;</span> <span class="n">ARC_CNT</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">B1111</span></div><div class='line' id='LC294'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">);</span></div><div class='line' id='LC295'><span class="p">}</span></div><div class='line' id='LC296'><br></div><div class='line' id='LC297'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC298'><br></div><div class='line' id='LC299'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">print_byte_register</span><span class="p">(</span><span class="k">const</span> <span class="kt">char</span><span class="o">*</span> <span class="n">name</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">qty</span><span class="p">)</span></div><div class='line' id='LC300'><span class="p">{</span></div><div class='line' id='LC301'>&nbsp;&nbsp;<span class="kt">char</span> <span class="n">extra_tab</span> <span class="o">=</span> <span class="n">strlen_P</span><span class="p">(</span><span class="n">name</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">8</span> <span class="o">?</span> <span class="sc">&#39;\t&#39;</span> <span class="o">:</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC302'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="n">PRIPSTR</span><span class="s">&quot;</span><span class="se">\t</span><span class="s">%c =&quot;</span><span class="p">),</span><span class="n">name</span><span class="p">,</span><span class="n">extra_tab</span><span class="p">);</span></div><div class='line' id='LC303'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">qty</span><span class="o">--</span><span class="p">)</span></div><div class='line' id='LC304'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot; 0x%02x&quot;</span><span class="p">),</span><span class="n">read_register</span><span class="p">(</span><span class="n">reg</span><span class="o">++</span><span class="p">));</span></div><div class='line' id='LC305'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">));</span></div><div class='line' id='LC306'><span class="p">}</span></div><div class='line' id='LC307'><br></div><div class='line' id='LC308'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC309'><br></div><div class='line' id='LC310'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">print_address_register</span><span class="p">(</span><span class="k">const</span> <span class="kt">char</span><span class="o">*</span> <span class="n">name</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">reg</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">qty</span><span class="p">)</span></div><div class='line' id='LC311'><span class="p">{</span></div><div class='line' id='LC312'>&nbsp;&nbsp;<span class="kt">char</span> <span class="n">extra_tab</span> <span class="o">=</span> <span class="n">strlen_P</span><span class="p">(</span><span class="n">name</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">8</span> <span class="o">?</span> <span class="sc">&#39;\t&#39;</span> <span class="o">:</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC313'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="n">PRIPSTR</span><span class="s">&quot;</span><span class="se">\t</span><span class="s">%c =&quot;</span><span class="p">),</span><span class="n">name</span><span class="p">,</span><span class="n">extra_tab</span><span class="p">);</span></div><div class='line' id='LC314'><br></div><div class='line' id='LC315'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">qty</span><span class="o">--</span><span class="p">)</span></div><div class='line' id='LC316'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC317'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">buffer</span><span class="p">[</span><span class="n">addr_width</span><span class="p">];</span></div><div class='line' id='LC318'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">read_register</span><span class="p">(</span><span class="n">reg</span><span class="o">++</span><span class="p">,</span><span class="n">buffer</span><span class="p">,</span><span class="k">sizeof</span> <span class="n">buffer</span><span class="p">);</span></div><div class='line' id='LC319'><br></div><div class='line' id='LC320'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot; 0x&quot;</span><span class="p">));</span></div><div class='line' id='LC321'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span><span class="o">*</span> <span class="n">bufptr</span> <span class="o">=</span> <span class="n">buffer</span> <span class="o">+</span> <span class="k">sizeof</span> <span class="n">buffer</span><span class="p">;</span></div><div class='line' id='LC322'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span><span class="p">(</span> <span class="o">--</span><span class="n">bufptr</span> <span class="o">&gt;=</span> <span class="n">buffer</span> <span class="p">)</span></div><div class='line' id='LC323'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;%02x&quot;</span><span class="p">),</span><span class="o">*</span><span class="n">bufptr</span><span class="p">);</span></div><div class='line' id='LC324'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC325'><br></div><div class='line' id='LC326'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">));</span></div><div class='line' id='LC327'><span class="p">}</span></div><div class='line' id='LC328'><br></div><div class='line' id='LC329'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC330'><br></div><div class='line' id='LC331'><span class="n">RF24</span><span class="o">::</span><span class="n">RF24</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">_cepin</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">_cspin</span><span class="p">)</span><span class="o">:</span></div><div class='line' id='LC332'>&nbsp;&nbsp;<span class="n">ce_pin</span><span class="p">(</span><span class="n">_cepin</span><span class="p">),</span> <span class="n">csn_pin</span><span class="p">(</span><span class="n">_cspin</span><span class="p">),</span> <span class="n">p_variant</span><span class="p">(</span><span class="nb">false</span><span class="p">),</span></div><div class='line' id='LC333'>&nbsp;&nbsp;<span class="n">payload_size</span><span class="p">(</span><span class="mi">32</span><span class="p">),</span> <span class="n">dynamic_payloads_enabled</span><span class="p">(</span><span class="nb">false</span><span class="p">),</span> <span class="n">addr_width</span><span class="p">(</span><span class="mi">5</span><span class="p">)</span><span class="c1">//,pipe0_reading_address(0)</span></div><div class='line' id='LC334'><span class="p">{</span></div><div class='line' id='LC335'><span class="p">}</span></div><div class='line' id='LC336'><br></div><div class='line' id='LC337'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC338'><br></div><div class='line' id='LC339'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setChannel</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">channel</span><span class="p">)</span></div><div class='line' id='LC340'><span class="p">{</span></div><div class='line' id='LC341'>&nbsp;&nbsp;<span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">max_channel</span> <span class="o">=</span> <span class="mi">127</span><span class="p">;</span></div><div class='line' id='LC342'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RF_CH</span><span class="p">,</span><span class="n">min</span><span class="p">(</span><span class="n">channel</span><span class="p">,</span><span class="n">max_channel</span><span class="p">));</span></div><div class='line' id='LC343'><span class="p">}</span></div><div class='line' id='LC344'><br></div><div class='line' id='LC345'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC346'><br></div><div class='line' id='LC347'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setPayloadSize</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">size</span><span class="p">)</span></div><div class='line' id='LC348'><span class="p">{</span></div><div class='line' id='LC349'>&nbsp;&nbsp;<span class="n">payload_size</span> <span class="o">=</span> <span class="n">min</span><span class="p">(</span><span class="n">size</span><span class="p">,</span><span class="mi">32</span><span class="p">);</span></div><div class='line' id='LC350'><span class="p">}</span></div><div class='line' id='LC351'><br></div><div class='line' id='LC352'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC353'><br></div><div class='line' id='LC354'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">getPayloadSize</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC355'><span class="p">{</span></div><div class='line' id='LC356'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">payload_size</span><span class="p">;</span></div><div class='line' id='LC357'><span class="p">}</span></div><div class='line' id='LC358'><br></div><div class='line' id='LC359'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC360'><br></div><div class='line' id='LC361'><span class="cp">#if !defined (MINIMAL)</span></div><div class='line' id='LC362'><br></div><div class='line' id='LC363'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_datarate_e_str_0</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;1MBPS&quot;</span><span class="p">;</span></div><div class='line' id='LC364'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_datarate_e_str_1</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;2MBPS&quot;</span><span class="p">;</span></div><div class='line' id='LC365'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_datarate_e_str_2</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;250KBPS&quot;</span><span class="p">;</span></div><div class='line' id='LC366'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="o">*</span> <span class="k">const</span> <span class="n">rf24_datarate_e_str_P</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC367'>&nbsp;&nbsp;<span class="n">rf24_datarate_e_str_0</span><span class="p">,</span></div><div class='line' id='LC368'>&nbsp;&nbsp;<span class="n">rf24_datarate_e_str_1</span><span class="p">,</span></div><div class='line' id='LC369'>&nbsp;&nbsp;<span class="n">rf24_datarate_e_str_2</span><span class="p">,</span></div><div class='line' id='LC370'><span class="p">};</span></div><div class='line' id='LC371'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_model_e_str_0</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;nRF24L01&quot;</span><span class="p">;</span></div><div class='line' id='LC372'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_model_e_str_1</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;nRF24L01+&quot;</span><span class="p">;</span></div><div class='line' id='LC373'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="o">*</span> <span class="k">const</span> <span class="n">rf24_model_e_str_P</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC374'>&nbsp;&nbsp;<span class="n">rf24_model_e_str_0</span><span class="p">,</span></div><div class='line' id='LC375'>&nbsp;&nbsp;<span class="n">rf24_model_e_str_1</span><span class="p">,</span></div><div class='line' id='LC376'><span class="p">};</span></div><div class='line' id='LC377'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_crclength_e_str_0</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;Disabled&quot;</span><span class="p">;</span></div><div class='line' id='LC378'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_crclength_e_str_1</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;8 bits&quot;</span><span class="p">;</span></div><div class='line' id='LC379'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_crclength_e_str_2</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;16 bits&quot;</span> <span class="p">;</span></div><div class='line' id='LC380'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="o">*</span> <span class="k">const</span> <span class="n">rf24_crclength_e_str_P</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC381'>&nbsp;&nbsp;<span class="n">rf24_crclength_e_str_0</span><span class="p">,</span></div><div class='line' id='LC382'>&nbsp;&nbsp;<span class="n">rf24_crclength_e_str_1</span><span class="p">,</span></div><div class='line' id='LC383'>&nbsp;&nbsp;<span class="n">rf24_crclength_e_str_2</span><span class="p">,</span></div><div class='line' id='LC384'><span class="p">};</span></div><div class='line' id='LC385'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_pa_dbm_e_str_0</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;PA_MIN&quot;</span><span class="p">;</span></div><div class='line' id='LC386'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_pa_dbm_e_str_1</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;PA_LOW&quot;</span><span class="p">;</span></div><div class='line' id='LC387'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_pa_dbm_e_str_2</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;PA_HIGH&quot;</span><span class="p">;</span></div><div class='line' id='LC388'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="n">rf24_pa_dbm_e_str_3</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="s">&quot;PA_MAX&quot;</span><span class="p">;</span></div><div class='line' id='LC389'><span class="k">static</span> <span class="k">const</span> <span class="kt">char</span> <span class="o">*</span> <span class="k">const</span> <span class="n">rf24_pa_dbm_e_str_P</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span> <span class="p">{</span></div><div class='line' id='LC390'>&nbsp;&nbsp;<span class="n">rf24_pa_dbm_e_str_0</span><span class="p">,</span></div><div class='line' id='LC391'>&nbsp;&nbsp;<span class="n">rf24_pa_dbm_e_str_1</span><span class="p">,</span></div><div class='line' id='LC392'>&nbsp;&nbsp;<span class="n">rf24_pa_dbm_e_str_2</span><span class="p">,</span></div><div class='line' id='LC393'>&nbsp;&nbsp;<span class="n">rf24_pa_dbm_e_str_3</span><span class="p">,</span></div><div class='line' id='LC394'><span class="p">};</span></div><div class='line' id='LC395'><br></div><div class='line' id='LC396'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">printDetails</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC397'><span class="p">{</span></div><div class='line' id='LC398'>&nbsp;&nbsp;<span class="n">print_status</span><span class="p">(</span><span class="n">get_status</span><span class="p">());</span></div><div class='line' id='LC399'><br></div><div class='line' id='LC400'>&nbsp;&nbsp;<span class="n">print_address_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;RX_ADDR_P0-1&quot;</span><span class="p">),</span><span class="n">RX_ADDR_P0</span><span class="p">,</span><span class="mi">2</span><span class="p">);</span></div><div class='line' id='LC401'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;RX_ADDR_P2-5&quot;</span><span class="p">),</span><span class="n">RX_ADDR_P2</span><span class="p">,</span><span class="mi">4</span><span class="p">);</span></div><div class='line' id='LC402'>&nbsp;&nbsp;<span class="n">print_address_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;TX_ADDR&quot;</span><span class="p">),</span><span class="n">TX_ADDR</span><span class="p">);</span></div><div class='line' id='LC403'><br></div><div class='line' id='LC404'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;RX_PW_P0-6&quot;</span><span class="p">),</span><span class="n">RX_PW_P0</span><span class="p">,</span><span class="mi">6</span><span class="p">);</span></div><div class='line' id='LC405'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;EN_AA&quot;</span><span class="p">),</span><span class="n">EN_AA</span><span class="p">);</span></div><div class='line' id='LC406'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;EN_RXADDR&quot;</span><span class="p">),</span><span class="n">EN_RXADDR</span><span class="p">);</span></div><div class='line' id='LC407'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;RF_CH&quot;</span><span class="p">),</span><span class="n">RF_CH</span><span class="p">);</span></div><div class='line' id='LC408'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;RF_SETUP&quot;</span><span class="p">),</span><span class="n">RF_SETUP</span><span class="p">);</span></div><div class='line' id='LC409'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;CONFIG&quot;</span><span class="p">),</span><span class="n">CONFIG</span><span class="p">);</span></div><div class='line' id='LC410'>&nbsp;&nbsp;<span class="n">print_byte_register</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;DYNPD/FEATURE&quot;</span><span class="p">),</span><span class="n">DYNPD</span><span class="p">,</span><span class="mi">2</span><span class="p">);</span></div><div class='line' id='LC411'><br></div><div class='line' id='LC412'><span class="cp">#if defined(__arm__)</span></div><div class='line' id='LC413'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;Data Rate</span><span class="se">\t</span><span class="s"> = %s</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_datarate_e_str_P</span><span class="p">[</span><span class="n">getDataRate</span><span class="p">()]));</span></div><div class='line' id='LC414'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;Model</span><span class="se">\t\t</span><span class="s"> = %s</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_model_e_str_P</span><span class="p">[</span><span class="n">isPVariant</span><span class="p">()]));</span></div><div class='line' id='LC415'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;CRC Length</span><span class="se">\t</span><span class="s"> = %s</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_crclength_e_str_P</span><span class="p">[</span><span class="n">getCRCLength</span><span class="p">()]));</span></div><div class='line' id='LC416'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;PA Power</span><span class="se">\t</span><span class="s"> = %s</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_pa_dbm_e_str_P</span><span class="p">[</span><span class="n">getPALevel</span><span class="p">()]));</span></div><div class='line' id='LC417'><span class="cp">#else</span></div><div class='line' id='LC418'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;Data Rate</span><span class="se">\t</span><span class="s"> = %S</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_datarate_e_str_P</span><span class="p">[</span><span class="n">getDataRate</span><span class="p">()]));</span></div><div class='line' id='LC419'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;Model</span><span class="se">\t\t</span><span class="s"> = %S</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_model_e_str_P</span><span class="p">[</span><span class="n">isPVariant</span><span class="p">()]));</span></div><div class='line' id='LC420'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;CRC Length</span><span class="se">\t</span><span class="s"> = %S</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_crclength_e_str_P</span><span class="p">[</span><span class="n">getCRCLength</span><span class="p">()]));</span></div><div class='line' id='LC421'>&nbsp;&nbsp;<span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;PA Power</span><span class="se">\t</span><span class="s"> = %S</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">),</span><span class="n">pgm_read_word</span><span class="p">(</span><span class="o">&amp;</span><span class="n">rf24_pa_dbm_e_str_P</span><span class="p">[</span><span class="n">getPALevel</span><span class="p">()]));</span></div><div class='line' id='LC422'><span class="cp">#endif</span></div><div class='line' id='LC423'><span class="p">}</span></div><div class='line' id='LC424'><br></div><div class='line' id='LC425'><span class="cp">#endif</span></div><div class='line' id='LC426'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC427'><br></div><div class='line' id='LC428'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">begin</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC429'><span class="p">{</span></div><div class='line' id='LC430'>&nbsp;&nbsp;<span class="c1">// Initialize pins</span></div><div class='line' id='LC431'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">ce_pin</span><span class="p">,</span><span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC432'><br></div><div class='line' id='LC433'><span class="cp">  #if defined(__arm__) &amp;&amp; ! defined( CORE_TEENSY )</span></div><div class='line' id='LC434'>&nbsp;&nbsp;	<span class="n">SPI</span><span class="p">.</span><span class="n">begin</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">);</span>					<span class="c1">// Using the extended SPI features of the DUE</span></div><div class='line' id='LC435'>	<span class="n">SPI</span><span class="p">.</span><span class="n">setClockDivider</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="mi">9</span><span class="p">);</span>   <span class="c1">// Set the bus speed to 8.4mhz on Due</span></div><div class='line' id='LC436'>	<span class="n">SPI</span><span class="p">.</span><span class="n">setBitOrder</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="n">MSBFIRST</span><span class="p">);</span>	<span class="c1">// Set the bit order and mode specific to this device</span></div><div class='line' id='LC437'>&nbsp;&nbsp;	<span class="n">SPI</span><span class="p">.</span><span class="n">setDataMode</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="n">SPI_MODE0</span><span class="p">);</span></div><div class='line' id='LC438'>	<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC439'>&nbsp;&nbsp;	<span class="c1">//csn(HIGH);</span></div><div class='line' id='LC440'><span class="cp">  #else</span></div><div class='line' id='LC441'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC442'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">begin</span><span class="p">();</span></div><div class='line' id='LC443'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC444'>&nbsp;&nbsp;	<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC445'><span class="cp">  #endif</span></div><div class='line' id='LC446'><br></div><div class='line' id='LC447'>&nbsp;&nbsp;<span class="c1">// Must allow the radio time to settle else configuration bits will not necessarily stick.</span></div><div class='line' id='LC448'>&nbsp;&nbsp;<span class="c1">// This is actually only required following power up but some settling time also appears to</span></div><div class='line' id='LC449'>&nbsp;&nbsp;<span class="c1">// be required after resets too. For full coverage, we&#39;ll always assume the worst.</span></div><div class='line' id='LC450'>&nbsp;&nbsp;<span class="c1">// Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.</span></div><div class='line' id='LC451'>&nbsp;&nbsp;<span class="c1">// Technically we require 4.5ms + 14us as a worst case. We&#39;ll just call it 5ms for good measure.</span></div><div class='line' id='LC452'>&nbsp;&nbsp;<span class="c1">// WARNING: Delay is based on P-variant whereby non-P *may* require different timing.</span></div><div class='line' id='LC453'>&nbsp;&nbsp;<span class="n">delay</span><span class="p">(</span> <span class="mi">5</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC454'><br></div><div class='line' id='LC455'>&nbsp;&nbsp;<span class="c1">// Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier</span></div><div class='line' id='LC456'>&nbsp;&nbsp;<span class="c1">// WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet</span></div><div class='line' id='LC457'>&nbsp;&nbsp;<span class="c1">// sizes must never be used. See documentation for a more complete explanation.</span></div><div class='line' id='LC458'>&nbsp;&nbsp;<span class="n">setRetries</span><span class="p">(</span><span class="mi">5</span><span class="p">,</span><span class="mi">15</span><span class="p">);</span></div><div class='line' id='LC459'><br></div><div class='line' id='LC460'>&nbsp;&nbsp;<span class="c1">// Reset value is MAX</span></div><div class='line' id='LC461'>&nbsp;&nbsp;<span class="c1">//setPALevel( RF24_PA_MAX ) ;</span></div><div class='line' id='LC462'><br></div><div class='line' id='LC463'>&nbsp;&nbsp;<span class="c1">// Determine if this is a p or non-p RF24 module and then</span></div><div class='line' id='LC464'>&nbsp;&nbsp;<span class="c1">// reset our data rate back to default value. This works</span></div><div class='line' id='LC465'>&nbsp;&nbsp;<span class="c1">// because a non-P variant won&#39;t allow the data rate to</span></div><div class='line' id='LC466'>&nbsp;&nbsp;<span class="c1">// be set to 250Kbps.</span></div><div class='line' id='LC467'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">setDataRate</span><span class="p">(</span> <span class="n">RF24_250KBPS</span> <span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC468'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC469'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">p_variant</span> <span class="o">=</span> <span class="nb">true</span> <span class="p">;</span></div><div class='line' id='LC470'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC471'><br></div><div class='line' id='LC472'>&nbsp;&nbsp;<span class="c1">// Then set the data rate to the slowest (and most reliable) speed supported by all</span></div><div class='line' id='LC473'>&nbsp;&nbsp;<span class="c1">// hardware.</span></div><div class='line' id='LC474'>&nbsp;&nbsp;<span class="n">setDataRate</span><span class="p">(</span> <span class="n">RF24_1MBPS</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC475'><br></div><div class='line' id='LC476'>&nbsp;&nbsp;<span class="c1">// Initialize CRC and request 2-byte (16bit) CRC</span></div><div class='line' id='LC477'>&nbsp;&nbsp;<span class="n">setCRCLength</span><span class="p">(</span> <span class="n">RF24_CRC_16</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC478'><br></div><div class='line' id='LC479'>&nbsp;&nbsp;<span class="c1">// Disable dynamic payloads, to match dynamic_payloads_enabled setting - Reset value is 0</span></div><div class='line' id='LC480'>&nbsp;&nbsp;<span class="c1">//write_register(DYNPD,0);</span></div><div class='line' id='LC481'><br></div><div class='line' id='LC482'>&nbsp;&nbsp;<span class="c1">// Reset current status</span></div><div class='line' id='LC483'>&nbsp;&nbsp;<span class="c1">// Notice reset and flush is the last thing we do</span></div><div class='line' id='LC484'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC485'><br></div><div class='line' id='LC486'>&nbsp;&nbsp;<span class="c1">// Set up default configuration.  Callers can always change it later.</span></div><div class='line' id='LC487'>&nbsp;&nbsp;<span class="c1">// This channel should be universally safe and not bleed over into adjacent</span></div><div class='line' id='LC488'>&nbsp;&nbsp;<span class="c1">// spectrum.</span></div><div class='line' id='LC489'>&nbsp;&nbsp;<span class="n">setChannel</span><span class="p">(</span><span class="mi">76</span><span class="p">);</span></div><div class='line' id='LC490'><br></div><div class='line' id='LC491'>&nbsp;&nbsp;<span class="c1">// Flush buffers</span></div><div class='line' id='LC492'>&nbsp;&nbsp;<span class="n">flush_rx</span><span class="p">();</span></div><div class='line' id='LC493'>&nbsp;&nbsp;<span class="n">flush_tx</span><span class="p">();</span></div><div class='line' id='LC494'><br></div><div class='line' id='LC495'>&nbsp;&nbsp;<span class="n">powerUp</span><span class="p">();</span> <span class="c1">//Power up by default when begin() is called</span></div><div class='line' id='LC496'><br></div><div class='line' id='LC497'>&nbsp;&nbsp;<span class="c1">// Enable PTX, do not write CE high so radio will remain in standby I mode ( 130us max to transition to RX or TX instead of 1500us from powerUp )</span></div><div class='line' id='LC498'>&nbsp;&nbsp;<span class="c1">// PTX should use only 22uA of power</span></div><div class='line' id='LC499'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">PRIM_RX</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC500'><br></div><div class='line' id='LC501'><span class="p">}</span></div><div class='line' id='LC502'><br></div><div class='line' id='LC503'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC504'><br></div><div class='line' id='LC505'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">startListening</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC506'><span class="p">{</span></div><div class='line' id='LC507'>&nbsp;&nbsp;<span class="n">powerUp</span><span class="p">();</span></div><div class='line' id='LC508'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">PRIM_RX</span><span class="p">));</span></div><div class='line' id='LC509'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC510'><br></div><div class='line' id='LC511'>&nbsp;&nbsp;<span class="c1">// Restore the pipe0 adddress, if exists</span></div><div class='line' id='LC512'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">pipe0_reading_address</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC513'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RX_ADDR_P0</span><span class="p">,</span> <span class="n">pipe0_reading_address</span><span class="p">,</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC514'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC515'><br></div><div class='line' id='LC516'>&nbsp;&nbsp;<span class="c1">// Flush buffers</span></div><div class='line' id='LC517'>&nbsp;&nbsp;<span class="c1">//flush_rx();</span></div><div class='line' id='LC518'>&nbsp;&nbsp;<span class="n">flush_tx</span><span class="p">();</span></div><div class='line' id='LC519'><br></div><div class='line' id='LC520'>&nbsp;&nbsp;<span class="c1">// Go!</span></div><div class='line' id='LC521'>&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC522'><br></div><div class='line' id='LC523'><span class="p">}</span></div><div class='line' id='LC524'><br></div><div class='line' id='LC525'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC526'><br></div><div class='line' id='LC527'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">stopListening</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC528'><span class="p">{</span></div><div class='line' id='LC529'><br></div><div class='line' id='LC530'>&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC531'><span class="cp">  #if defined(__arm__)</span></div><div class='line' id='LC532'>&nbsp;&nbsp;	<span class="n">delayMicroseconds</span><span class="p">(</span><span class="mi">130</span><span class="p">);</span></div><div class='line' id='LC533'><span class="cp">  #endif</span></div><div class='line' id='LC534'>&nbsp;&nbsp;<span class="n">flush_tx</span><span class="p">();</span></div><div class='line' id='LC535'>&nbsp;&nbsp;<span class="c1">//flush_rx();</span></div><div class='line' id='LC536'><br></div><div class='line' id='LC537'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">PRIM_RX</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC538'>&nbsp;&nbsp;<span class="n">delayMicroseconds</span><span class="p">(</span><span class="mi">130</span><span class="p">);</span> <span class="c1">//Found that adding this delay back actually increases response time</span></div><div class='line' id='LC539'><span class="p">}</span></div><div class='line' id='LC540'><br></div><div class='line' id='LC541'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC542'><br></div><div class='line' id='LC543'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">powerDown</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC544'><span class="p">{</span></div><div class='line' id='LC545'>&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span> <span class="c1">// Guarantee CE is low on powerDown</span></div><div class='line' id='LC546'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">PWR_UP</span><span class="p">));</span></div><div class='line' id='LC547'><span class="p">}</span></div><div class='line' id='LC548'><br></div><div class='line' id='LC549'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC550'><br></div><div class='line' id='LC551'><span class="c1">//Power up now. Radio will not power down unless instructed by MCU for config changes etc.</span></div><div class='line' id='LC552'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">powerUp</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC553'><span class="p">{</span></div><div class='line' id='LC554'>&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">cfg</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">);</span></div><div class='line' id='LC555'><br></div><div class='line' id='LC556'>&nbsp;&nbsp;&nbsp;<span class="c1">// if not powered up then power up and wait for the radio to initialize</span></div><div class='line' id='LC557'>&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="p">(</span><span class="n">cfg</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">PWR_UP</span><span class="p">))){</span></div><div class='line' id='LC558'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">PWR_UP</span><span class="p">));</span></div><div class='line' id='LC559'><br></div><div class='line' id='LC560'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode.</span></div><div class='line' id='LC561'>	  <span class="c1">// There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before</span></div><div class='line' id='LC562'>	  <span class="c1">// the CEis set high. - Tpd2stby can be up to 5ms per the 1.0 datasheet</span></div><div class='line' id='LC563'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">delay</span><span class="p">(</span><span class="mi">5</span><span class="p">);</span></div><div class='line' id='LC564'><br></div><div class='line' id='LC565'>&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC566'><span class="p">}</span></div><div class='line' id='LC567'><br></div><div class='line' id='LC568'><span class="cm">/******************************************************************/</span></div><div class='line' id='LC569'><span class="cp">#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC570'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">errNotify</span><span class="p">(){</span></div><div class='line' id='LC571'>	<span class="n">IF_SERIAL_DEBUG</span><span class="p">(</span><span class="n">printf_P</span><span class="p">(</span><span class="n">PSTR</span><span class="p">(</span><span class="s">&quot;HARDWARE FAIL</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">)));</span></div><div class='line' id='LC572'>	<span class="n">failureDetected</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC573'><span class="p">}</span></div><div class='line' id='LC574'><span class="cp">#endif</span></div><div class='line' id='LC575'><span class="cm">/******************************************************************/</span></div><div class='line' id='LC576'><br></div><div class='line' id='LC577'><span class="c1">//Similar to the previous write, clears the interrupt flags</span></div><div class='line' id='LC578'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">write</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">)</span></div><div class='line' id='LC579'><span class="p">{</span></div><div class='line' id='LC580'>	<span class="c1">//Start Writing</span></div><div class='line' id='LC581'>	<span class="n">startFastWrite</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span><span class="n">len</span><span class="p">,</span><span class="n">multicast</span><span class="p">);</span></div><div class='line' id='LC582'><br></div><div class='line' id='LC583'>	<span class="c1">//Wait until complete or failed</span></div><div class='line' id='LC584'><span class="cp">	#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC585'>		<span class="kt">uint32_t</span> <span class="n">timer</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC586'><span class="cp">	#endif </span></div><div class='line' id='LC587'><br></div><div class='line' id='LC588'>	<span class="k">while</span><span class="p">(</span> <span class="o">!</span> <span class="p">(</span> <span class="n">get_status</span><span class="p">()</span>  <span class="o">&amp;</span> <span class="p">(</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">)))</span> <span class="p">{</span> </div><div class='line' id='LC589'>		<span class="err">#</span><span class="k">if</span> <span class="n">defined</span> <span class="p">(</span><span class="n">FAILURE_HANDLING</span><span class="p">)</span></div><div class='line' id='LC590'>			<span class="k">if</span><span class="p">(</span><span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">timer</span> <span class="o">&gt;</span> <span class="mi">75</span><span class="p">){</span>			</div><div class='line' id='LC591'>				<span class="n">errNotify</span><span class="p">();</span></div><div class='line' id='LC592'>				<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>							</div><div class='line' id='LC593'>			<span class="p">}</span></div><div class='line' id='LC594'><span class="cp">		#endif</span></div><div class='line' id='LC595'>	<span class="p">}</span></div><div class='line' id='LC596'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC597'>	<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC598'><br></div><div class='line' id='LC599'>	<span class="kt">uint8_t</span> <span class="n">status</span> <span class="o">=</span> <span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC600'><br></div><div class='line' id='LC601'>&nbsp;&nbsp;<span class="c1">//Max retries exceeded</span></div><div class='line' id='LC602'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)){</span></div><div class='line' id='LC603'>&nbsp;&nbsp;	<span class="n">flush_tx</span><span class="p">();</span> <span class="c1">//Only going to be 1 packet int the FIFO at a time using this method, so just flush</span></div><div class='line' id='LC604'>&nbsp;&nbsp;	<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC605'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC606'>	<span class="c1">//TX OK 1 or 0</span></div><div class='line' id='LC607'>&nbsp;&nbsp;<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC608'><span class="p">}</span></div><div class='line' id='LC609'><br></div><div class='line' id='LC610'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">write</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">){</span></div><div class='line' id='LC611'>	<span class="k">return</span> <span class="n">write</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span><span class="n">len</span><span class="p">,</span><span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC612'><span class="p">}</span></div><div class='line' id='LC613'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC614'><br></div><div class='line' id='LC615'><span class="c1">//For general use, the interrupt flags are not important to clear</span></div><div class='line' id='LC616'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">writeBlocking</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="kt">uint32_t</span> <span class="n">timeout</span> <span class="p">)</span></div><div class='line' id='LC617'><span class="p">{</span></div><div class='line' id='LC618'>	<span class="c1">//Block until the FIFO is NOT full.</span></div><div class='line' id='LC619'>	<span class="c1">//Keep track of the MAX retries and set auto-retry if seeing failures</span></div><div class='line' id='LC620'>	<span class="c1">//This way the FIFO will fill up and allow blocking until packets go through</span></div><div class='line' id='LC621'>	<span class="c1">//The radio will auto-clear everything in the FIFO as long as CE remains high</span></div><div class='line' id='LC622'><br></div><div class='line' id='LC623'>	<span class="kt">uint32_t</span> <span class="n">timer</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span>							  <span class="c1">//Get the time that the payload transmission started</span></div><div class='line' id='LC624'><br></div><div class='line' id='LC625'>	<span class="k">while</span><span class="p">(</span> <span class="p">(</span> <span class="n">get_status</span><span class="p">()</span>  <span class="o">&amp;</span> <span class="p">(</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_FULL</span><span class="p">)</span> <span class="p">)))</span> <span class="p">{</span>		  <span class="c1">//Blocking only if FIFO is full. This will loop and block until TX is successful or timeout</span></div><div class='line' id='LC626'><br></div><div class='line' id='LC627'>		<span class="k">if</span><span class="p">(</span> <span class="n">get_status</span><span class="p">()</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)){</span>					  <span class="c1">//If MAX Retries have been reached</span></div><div class='line' id='LC628'>			<span class="n">reUseTX</span><span class="p">();</span>										  <span class="c1">//Set re-transmit and clear the MAX_RT interrupt flag</span></div><div class='line' id='LC629'>			<span class="k">if</span><span class="p">(</span><span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">timer</span> <span class="o">&gt;</span> <span class="n">timeout</span><span class="p">){</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span> <span class="p">}</span>		  <span class="c1">//If this payload has exceeded the user-defined timeout, exit and return 0</span></div><div class='line' id='LC630'>		<span class="p">}</span></div><div class='line' id='LC631'><span class="cp">		#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC632'>			<span class="k">if</span><span class="p">(</span><span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">timer</span> <span class="o">&gt;</span> <span class="p">(</span><span class="n">timeout</span><span class="o">+</span><span class="mi">75</span><span class="p">)</span> <span class="p">){</span>			</div><div class='line' id='LC633'>				<span class="n">errNotify</span><span class="p">();</span></div><div class='line' id='LC634'>				<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>							</div><div class='line' id='LC635'>			<span class="p">}</span></div><div class='line' id='LC636'><span class="cp">		#endif</span></div><div class='line' id='LC637'><br></div><div class='line' id='LC638'>&nbsp;&nbsp;	<span class="p">}</span></div><div class='line' id='LC639'><br></div><div class='line' id='LC640'>&nbsp;&nbsp;	<span class="c1">//Start Writing</span></div><div class='line' id='LC641'>	<span class="n">startFastWrite</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span><span class="n">len</span><span class="p">,</span><span class="mi">0</span><span class="p">);</span>								  <span class="c1">//Write the payload if a buffer is clear</span></div><div class='line' id='LC642'><br></div><div class='line' id='LC643'>	<span class="k">return</span> <span class="mi">1</span><span class="p">;</span>												  <span class="c1">//Return 1 to indicate successful transmission</span></div><div class='line' id='LC644'><span class="p">}</span></div><div class='line' id='LC645'><br></div><div class='line' id='LC646'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC647'><br></div><div class='line' id='LC648'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">reUseTX</span><span class="p">(){</span></div><div class='line' id='LC649'>		<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span>			  <span class="c1">//Clear max retry flag</span></div><div class='line' id='LC650'>		<span class="n">spiTrans</span><span class="p">(</span> <span class="n">REUSE_TX_PL</span> <span class="p">);</span></div><div class='line' id='LC651'>		<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span>										  <span class="c1">//Re-Transfer packet</span></div><div class='line' id='LC652'>		<span class="n">ce</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC653'><span class="p">}</span></div><div class='line' id='LC654'><br></div><div class='line' id='LC655'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC656'><br></div><div class='line' id='LC657'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">writeFast</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">)</span></div><div class='line' id='LC658'><span class="p">{</span></div><div class='line' id='LC659'>	<span class="c1">//Block until the FIFO is NOT full.</span></div><div class='line' id='LC660'>	<span class="c1">//Keep track of the MAX retries and set auto-retry if seeing failures</span></div><div class='line' id='LC661'>	<span class="c1">//Return 0 so the user can control the retrys and set a timer or failure counter if required</span></div><div class='line' id='LC662'>	<span class="c1">//The radio will auto-clear everything in the FIFO as long as CE remains high</span></div><div class='line' id='LC663'><br></div><div class='line' id='LC664'><span class="cp">	#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC665'>		<span class="kt">uint32_t</span> <span class="n">timer</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC666'><span class="cp">	#endif</span></div><div class='line' id='LC667'><br></div><div class='line' id='LC668'>	<span class="k">while</span><span class="p">(</span> <span class="p">(</span> <span class="n">get_status</span><span class="p">()</span>  <span class="o">&amp;</span> <span class="p">(</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_FULL</span><span class="p">)</span> <span class="p">)))</span> <span class="p">{</span>			  <span class="c1">//Blocking only if FIFO is full. This will loop and block until TX is successful or fail</span></div><div class='line' id='LC669'><br></div><div class='line' id='LC670'>		<span class="k">if</span><span class="p">(</span> <span class="n">get_status</span><span class="p">()</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)){</span></div><div class='line' id='LC671'>			<span class="c1">//reUseTX();										  //Set re-transmit</span></div><div class='line' id='LC672'>			<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span>			  <span class="c1">//Clear max retry flag</span></div><div class='line' id='LC673'>			<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>										  <span class="c1">//Return 0. The previous payload has been retransmitted</span></div><div class='line' id='LC674'>															  <span class="c1">//From the user perspective, if you get a 0, just keep trying to send the same payload</span></div><div class='line' id='LC675'>		<span class="p">}</span></div><div class='line' id='LC676'><span class="cp">		#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC677'>			<span class="k">if</span><span class="p">(</span><span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">timer</span> <span class="o">&gt;</span> <span class="mi">75</span> <span class="p">){</span>			</div><div class='line' id='LC678'>				<span class="n">errNotify</span><span class="p">();</span></div><div class='line' id='LC679'>				<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>							</div><div class='line' id='LC680'>			<span class="p">}</span></div><div class='line' id='LC681'><span class="cp">		#endif</span></div><div class='line' id='LC682'>&nbsp;&nbsp;	<span class="p">}</span></div><div class='line' id='LC683'>		     <span class="c1">//Start Writing</span></div><div class='line' id='LC684'>	<span class="n">startFastWrite</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span><span class="n">len</span><span class="p">,</span><span class="n">multicast</span><span class="p">);</span></div><div class='line' id='LC685'><br></div><div class='line' id='LC686'>	<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC687'><span class="p">}</span></div><div class='line' id='LC688'><br></div><div class='line' id='LC689'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">writeFast</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">){</span></div><div class='line' id='LC690'>	<span class="k">return</span> <span class="n">writeFast</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span><span class="n">len</span><span class="p">,</span><span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC691'><span class="p">}</span></div><div class='line' id='LC692'><br></div><div class='line' id='LC693'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC694'><br></div><div class='line' id='LC695'><span class="c1">//Per the documentation, we want to set PTX Mode when not listening. Then all we do is write data and set CE high</span></div><div class='line' id='LC696'><span class="c1">//In this mode, if we can keep the FIFO buffers loaded, packets will transmit immediately (no 130us delay)</span></div><div class='line' id='LC697'><span class="c1">//Otherwise we enter Standby-II mode, which is still faster than standby mode</span></div><div class='line' id='LC698'><span class="c1">//Also, we remove the need to keep writing the config register over and over and delaying for 150 us each time if sending a stream of data</span></div><div class='line' id='LC699'><br></div><div class='line' id='LC700'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">startFastWrite</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span><span class="p">){</span> <span class="c1">//TMRh20</span></div><div class='line' id='LC701'><br></div><div class='line' id='LC702'>	<span class="c1">//write_payload( buf,len);</span></div><div class='line' id='LC703'>	<span class="n">write_payload</span><span class="p">(</span> <span class="n">buf</span><span class="p">,</span> <span class="n">len</span><span class="p">,</span><span class="n">multicast</span> <span class="o">?</span> <span class="nl">W_TX_PAYLOAD_NO_ACK</span> <span class="p">:</span> <span class="n">W_TX_PAYLOAD</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC704'>	<span class="n">ce</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC705'><br></div><div class='line' id='LC706'><span class="p">}</span></div><div class='line' id='LC707'><br></div><div class='line' id='LC708'><br></div><div class='line' id='LC709'><span class="c1">//Added the original startWrite back in so users can still use interrupts, ack payloads, etc</span></div><div class='line' id='LC710'><span class="c1">//Allows the library to pass all tests</span></div><div class='line' id='LC711'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">startWrite</span><span class="p">(</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">,</span> <span class="k">const</span> <span class="kt">bool</span> <span class="n">multicast</span> <span class="p">){</span></div><div class='line' id='LC712'><br></div><div class='line' id='LC713'>&nbsp;&nbsp;<span class="c1">// Send the payload</span></div><div class='line' id='LC714'><br></div><div class='line' id='LC715'>&nbsp;&nbsp;<span class="c1">//write_payload( buf, len );</span></div><div class='line' id='LC716'>&nbsp;&nbsp;<span class="n">write_payload</span><span class="p">(</span> <span class="n">buf</span><span class="p">,</span> <span class="n">len</span><span class="p">,</span><span class="n">multicast</span><span class="o">?</span> <span class="nl">W_TX_PAYLOAD_NO_ACK</span> <span class="p">:</span> <span class="n">W_TX_PAYLOAD</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC717'>&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC718'><span class="cp">  #if defined(CORE_TEENSY) || !defined(ARDUINO)</span></div><div class='line' id='LC719'>	<span class="n">delayMicroseconds</span><span class="p">(</span><span class="mi">10</span><span class="p">);</span></div><div class='line' id='LC720'><span class="cp">  #endif</span></div><div class='line' id='LC721'>&nbsp;&nbsp;<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC722'><br></div><div class='line' id='LC723'><br></div><div class='line' id='LC724'><span class="p">}</span></div><div class='line' id='LC725'><br></div><div class='line' id='LC726'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">txStandBy</span><span class="p">(){</span></div><div class='line' id='LC727'><span class="cp">    #if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC728'>		<span class="kt">uint32_t</span> <span class="n">timeout</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC729'><span class="cp">	#endif</span></div><div class='line' id='LC730'>	<span class="k">while</span><span class="p">(</span> <span class="o">!</span> <span class="p">(</span><span class="n">read_register</span><span class="p">(</span><span class="n">FIFO_STATUS</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_EMPTY</span><span class="p">))</span> <span class="p">){</span></div><div class='line' id='LC731'>		<span class="k">if</span><span class="p">(</span> <span class="n">get_status</span><span class="p">()</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)){</span></div><div class='line' id='LC732'>			<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC733'>			<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC734'>			<span class="n">flush_tx</span><span class="p">();</span>    <span class="c1">//Non blocking, flush the data</span></div><div class='line' id='LC735'>			<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC736'>		<span class="p">}</span></div><div class='line' id='LC737'><span class="cp">		#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC738'>			<span class="k">if</span><span class="p">(</span> <span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">timeout</span> <span class="o">&gt;</span> <span class="mi">75</span><span class="p">){</span></div><div class='line' id='LC739'>				<span class="n">errNotify</span><span class="p">();</span></div><div class='line' id='LC740'>				<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>	</div><div class='line' id='LC741'>			<span class="p">}</span></div><div class='line' id='LC742'><span class="cp">		#endif</span></div><div class='line' id='LC743'>	<span class="p">}</span></div><div class='line' id='LC744'><br></div><div class='line' id='LC745'>	<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span>			   <span class="c1">//Set STANDBY-I mode</span></div><div class='line' id='LC746'>	<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC747'><span class="p">}</span></div><div class='line' id='LC748'><br></div><div class='line' id='LC749'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">txStandBy</span><span class="p">(</span><span class="kt">uint32_t</span> <span class="n">timeout</span><span class="p">){</span></div><div class='line' id='LC750'><br></div><div class='line' id='LC751'>	<span class="kt">uint32_t</span> <span class="n">start</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC752'><br></div><div class='line' id='LC753'>	<span class="k">while</span><span class="p">(</span> <span class="o">!</span> <span class="p">(</span><span class="n">read_register</span><span class="p">(</span><span class="n">FIFO_STATUS</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_EMPTY</span><span class="p">))</span> <span class="p">){</span></div><div class='line' id='LC754'>		<span class="k">if</span><span class="p">(</span> <span class="n">get_status</span><span class="p">()</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)){</span></div><div class='line' id='LC755'>			<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC756'>				<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span>										  <span class="c1">//Set re-transmit</span></div><div class='line' id='LC757'>				<span class="n">ce</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC758'>				<span class="k">if</span><span class="p">(</span><span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">start</span> <span class="o">&gt;=</span> <span class="n">timeout</span><span class="p">){</span></div><div class='line' id='LC759'>					<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span> <span class="n">flush_tx</span><span class="p">();</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC760'>				<span class="p">}</span></div><div class='line' id='LC761'>		<span class="p">}</span></div><div class='line' id='LC762'><span class="cp">		#if defined (FAILURE_HANDLING)</span></div><div class='line' id='LC763'>			<span class="k">if</span><span class="p">(</span> <span class="n">millis</span><span class="p">()</span> <span class="o">-</span> <span class="n">start</span> <span class="o">&gt;</span> <span class="p">(</span><span class="n">timeout</span><span class="o">+</span><span class="mi">75</span><span class="p">)){</span></div><div class='line' id='LC764'>				<span class="n">errNotify</span><span class="p">();</span></div><div class='line' id='LC765'>				<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>	</div><div class='line' id='LC766'>			<span class="p">}</span></div><div class='line' id='LC767'><span class="cp">		#endif</span></div><div class='line' id='LC768'>	<span class="p">}</span></div><div class='line' id='LC769'><br></div><div class='line' id='LC770'><br></div><div class='line' id='LC771'>	<span class="n">ce</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span>				   <span class="c1">//Set STANDBY-I mode</span></div><div class='line' id='LC772'>	<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC773'><br></div><div class='line' id='LC774'><span class="p">}</span></div><div class='line' id='LC775'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC776'><br></div><div class='line' id='LC777'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">maskIRQ</span><span class="p">(</span><span class="kt">bool</span> <span class="n">tx</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">fail</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">rx</span><span class="p">){</span></div><div class='line' id='LC778'><br></div><div class='line' id='LC779'>	<span class="n">write_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">,</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="p">)</span> <span class="o">|</span> <span class="n">fail</span> <span class="o">&lt;&lt;</span> <span class="n">MASK_MAX_RT</span> <span class="o">|</span> <span class="n">tx</span> <span class="o">&lt;&lt;</span> <span class="n">MASK_TX_DS</span> <span class="o">|</span> <span class="n">rx</span> <span class="o">&lt;&lt;</span> <span class="n">MASK_RX_DR</span>  <span class="p">);</span></div><div class='line' id='LC780'><span class="p">}</span></div><div class='line' id='LC781'><br></div><div class='line' id='LC782'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC783'><br></div><div class='line' id='LC784'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">getDynamicPayloadSize</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC785'><span class="p">{</span></div><div class='line' id='LC786'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">result</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC787'><br></div><div class='line' id='LC788'><span class="cp">  #if defined (__arm__) &amp;&amp; ! defined( CORE_TEENSY )</span></div><div class='line' id='LC789'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">R_RX_PL_WID</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span> <span class="p">);</span></div><div class='line' id='LC790'>&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC791'><span class="cp">  #else</span></div><div class='line' id='LC792'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC793'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">R_RX_PL_WID</span> <span class="p">);</span></div><div class='line' id='LC794'>&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="mh">0xff</span><span class="p">);</span></div><div class='line' id='LC795'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC796'><br></div><div class='line' id='LC797'><span class="cp">  #endif</span></div><div class='line' id='LC798'><br></div><div class='line' id='LC799'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">result</span> <span class="o">&gt;</span> <span class="mi">32</span><span class="p">)</span> <span class="p">{</span> <span class="n">flush_rx</span><span class="p">();</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span> <span class="p">}</span></div><div class='line' id='LC800'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">result</span><span class="p">;</span></div><div class='line' id='LC801'><span class="p">}</span></div><div class='line' id='LC802'><br></div><div class='line' id='LC803'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC804'><br></div><div class='line' id='LC805'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">available</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC806'><span class="p">{</span></div><div class='line' id='LC807'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">available</span><span class="p">(</span><span class="nb">NULL</span><span class="p">);</span></div><div class='line' id='LC808'><span class="p">}</span></div><div class='line' id='LC809'><br></div><div class='line' id='LC810'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC811'><br></div><div class='line' id='LC812'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">available</span><span class="p">(</span><span class="kt">uint8_t</span><span class="o">*</span> <span class="n">pipe_num</span><span class="p">)</span></div><div class='line' id='LC813'><span class="p">{</span></div><div class='line' id='LC814'><br></div><div class='line' id='LC815'>&nbsp;&nbsp;<span class="c1">//Check the FIFO buffer to see if data is waitng to be read</span></div><div class='line' id='LC816'><br></div><div class='line' id='LC817'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">FIFO_STATUS</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RX_EMPTY</span><span class="p">)</span> <span class="p">)){</span></div><div class='line' id='LC818'><br></div><div class='line' id='LC819'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// If the caller wants the pipe number, include that</span></div><div class='line' id='LC820'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">pipe_num</span> <span class="p">){</span></div><div class='line' id='LC821'>	  <span class="kt">uint8_t</span> <span class="n">status</span> <span class="o">=</span> <span class="n">get_status</span><span class="p">();</span></div><div class='line' id='LC822'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">pipe_num</span> <span class="o">=</span> <span class="p">(</span> <span class="n">status</span> <span class="o">&gt;&gt;</span> <span class="n">RX_P_NO</span> <span class="p">)</span> <span class="o">&amp;</span> <span class="n">B111</span><span class="p">;</span></div><div class='line' id='LC823'>&nbsp;&nbsp;	<span class="p">}</span></div><div class='line' id='LC824'>&nbsp;&nbsp;	<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC825'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC826'><br></div><div class='line' id='LC827'><br></div><div class='line' id='LC828'>&nbsp;&nbsp;<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC829'><br></div><div class='line' id='LC830'><br></div><div class='line' id='LC831'><span class="p">}</span></div><div class='line' id='LC832'><br></div><div class='line' id='LC833'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC834'><br></div><div class='line' id='LC835'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">read</span><span class="p">(</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span> <span class="p">){</span></div><div class='line' id='LC836'><br></div><div class='line' id='LC837'>&nbsp;&nbsp;<span class="c1">// Fetch the payload</span></div><div class='line' id='LC838'>&nbsp;&nbsp;<span class="n">read_payload</span><span class="p">(</span> <span class="n">buf</span><span class="p">,</span> <span class="n">len</span> <span class="p">);</span></div><div class='line' id='LC839'><br></div><div class='line' id='LC840'>&nbsp;&nbsp;<span class="c1">//Clear the two possible interrupt flags with one command</span></div><div class='line' id='LC841'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC842'><br></div><div class='line' id='LC843'><span class="p">}</span></div><div class='line' id='LC844'><br></div><div class='line' id='LC845'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC846'><br></div><div class='line' id='LC847'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">whatHappened</span><span class="p">(</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">tx_ok</span><span class="p">,</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">tx_fail</span><span class="p">,</span><span class="kt">bool</span><span class="o">&amp;</span> <span class="n">rx_ready</span><span class="p">)</span></div><div class='line' id='LC848'><span class="p">{</span></div><div class='line' id='LC849'>&nbsp;&nbsp;<span class="c1">// Read the status &amp; reset the status in one easy call</span></div><div class='line' id='LC850'>&nbsp;&nbsp;<span class="c1">// Or is that such a good idea?</span></div><div class='line' id='LC851'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">status</span> <span class="o">=</span> <span class="n">write_register</span><span class="p">(</span><span class="n">STATUS</span><span class="p">,</span><span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC852'><br></div><div class='line' id='LC853'>&nbsp;&nbsp;<span class="c1">// Report to the user what happened</span></div><div class='line' id='LC854'>&nbsp;&nbsp;<span class="n">tx_ok</span> <span class="o">=</span> <span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">TX_DS</span><span class="p">);</span></div><div class='line' id='LC855'>&nbsp;&nbsp;<span class="n">tx_fail</span> <span class="o">=</span> <span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">MAX_RT</span><span class="p">);</span></div><div class='line' id='LC856'>&nbsp;&nbsp;<span class="n">rx_ready</span> <span class="o">=</span> <span class="n">status</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RX_DR</span><span class="p">);</span></div><div class='line' id='LC857'><span class="p">}</span></div><div class='line' id='LC858'><br></div><div class='line' id='LC859'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC860'><br></div><div class='line' id='LC861'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">openWritingPipe</span><span class="p">(</span><span class="kt">uint64_t</span> <span class="n">value</span><span class="p">)</span></div><div class='line' id='LC862'><span class="p">{</span></div><div class='line' id='LC863'>&nbsp;&nbsp;<span class="c1">// Note that AVR 8-bit uC&#39;s store this LSB first, and the NRF24L01(+)</span></div><div class='line' id='LC864'>&nbsp;&nbsp;<span class="c1">// expects it LSB first too, so we&#39;re good.</span></div><div class='line' id='LC865'><br></div><div class='line' id='LC866'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RX_ADDR_P0</span><span class="p">,</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="o">&amp;</span><span class="n">value</span><span class="p">),</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC867'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">TX_ADDR</span><span class="p">,</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="o">&amp;</span><span class="n">value</span><span class="p">),</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC868'><br></div><div class='line' id='LC869'>&nbsp;&nbsp;<span class="c1">//const uint8_t max_payload_size = 32;</span></div><div class='line' id='LC870'>&nbsp;&nbsp;<span class="c1">//write_register(RX_PW_P0,min(payload_size,max_payload_size));</span></div><div class='line' id='LC871'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RX_PW_P0</span><span class="p">,</span><span class="n">payload_size</span><span class="p">);</span></div><div class='line' id='LC872'><span class="p">}</span></div><div class='line' id='LC873'><br></div><div class='line' id='LC874'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC875'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">openWritingPipe</span><span class="p">(</span><span class="k">const</span> <span class="kt">uint8_t</span> <span class="o">*</span><span class="n">address</span><span class="p">)</span></div><div class='line' id='LC876'><span class="p">{</span></div><div class='line' id='LC877'>&nbsp;&nbsp;<span class="c1">// Note that AVR 8-bit uC&#39;s store this LSB first, and the NRF24L01(+)</span></div><div class='line' id='LC878'>&nbsp;&nbsp;<span class="c1">// expects it LSB first too, so we&#39;re good.</span></div><div class='line' id='LC879'><br></div><div class='line' id='LC880'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RX_ADDR_P0</span><span class="p">,</span><span class="n">address</span><span class="p">,</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC881'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">TX_ADDR</span><span class="p">,</span> <span class="n">address</span><span class="p">,</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC882'><br></div><div class='line' id='LC883'>&nbsp;&nbsp;<span class="c1">//const uint8_t max_payload_size = 32;</span></div><div class='line' id='LC884'>&nbsp;&nbsp;<span class="c1">//write_register(RX_PW_P0,min(payload_size,max_payload_size));</span></div><div class='line' id='LC885'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RX_PW_P0</span><span class="p">,</span><span class="n">payload_size</span><span class="p">);</span></div><div class='line' id='LC886'><span class="p">}</span></div><div class='line' id='LC887'><br></div><div class='line' id='LC888'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC889'><span class="k">static</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">child_pipe</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span></div><div class='line' id='LC890'><span class="p">{</span></div><div class='line' id='LC891'>&nbsp;&nbsp;<span class="n">RX_ADDR_P0</span><span class="p">,</span> <span class="n">RX_ADDR_P1</span><span class="p">,</span> <span class="n">RX_ADDR_P2</span><span class="p">,</span> <span class="n">RX_ADDR_P3</span><span class="p">,</span> <span class="n">RX_ADDR_P4</span><span class="p">,</span> <span class="n">RX_ADDR_P5</span></div><div class='line' id='LC892'><span class="p">};</span></div><div class='line' id='LC893'><span class="k">static</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">child_payload_size</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span></div><div class='line' id='LC894'><span class="p">{</span></div><div class='line' id='LC895'>&nbsp;&nbsp;<span class="n">RX_PW_P0</span><span class="p">,</span> <span class="n">RX_PW_P1</span><span class="p">,</span> <span class="n">RX_PW_P2</span><span class="p">,</span> <span class="n">RX_PW_P3</span><span class="p">,</span> <span class="n">RX_PW_P4</span><span class="p">,</span> <span class="n">RX_PW_P5</span></div><div class='line' id='LC896'><span class="p">};</span></div><div class='line' id='LC897'><span class="k">static</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">child_pipe_enable</span><span class="p">[]</span> <span class="n">PROGMEM</span> <span class="o">=</span></div><div class='line' id='LC898'><span class="p">{</span></div><div class='line' id='LC899'>&nbsp;&nbsp;<span class="n">ERX_P0</span><span class="p">,</span> <span class="n">ERX_P1</span><span class="p">,</span> <span class="n">ERX_P2</span><span class="p">,</span> <span class="n">ERX_P3</span><span class="p">,</span> <span class="n">ERX_P4</span><span class="p">,</span> <span class="n">ERX_P5</span></div><div class='line' id='LC900'><span class="p">};</span></div><div class='line' id='LC901'><br></div><div class='line' id='LC902'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">openReadingPipe</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">child</span><span class="p">,</span> <span class="kt">uint64_t</span> <span class="n">address</span><span class="p">)</span></div><div class='line' id='LC903'><span class="p">{</span></div><div class='line' id='LC904'>&nbsp;&nbsp;<span class="c1">// If this is pipe 0, cache the address.  This is needed because</span></div><div class='line' id='LC905'>&nbsp;&nbsp;<span class="c1">// openWritingPipe() will overwrite the pipe 0 address, so</span></div><div class='line' id='LC906'>&nbsp;&nbsp;<span class="c1">// startListening() will have to restore it.</span></div><div class='line' id='LC907'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">child</span> <span class="o">==</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC908'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">memcpy</span><span class="p">(</span><span class="n">pipe0_reading_address</span><span class="p">,</span><span class="o">&amp;</span><span class="n">address</span><span class="p">,</span><span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC909'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC910'><br></div><div class='line' id='LC911'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">child</span> <span class="o">&lt;=</span> <span class="mi">6</span><span class="p">)</span></div><div class='line' id='LC912'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC913'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// For pipes 2-5, only write the LSB</span></div><div class='line' id='LC914'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">child</span> <span class="o">&lt;</span> <span class="mi">2</span> <span class="p">)</span></div><div class='line' id='LC915'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="o">&amp;</span><span class="n">address</span><span class="p">),</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC916'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC917'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="nf">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="o">&amp;</span><span class="n">address</span><span class="p">),</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC918'><br></div><div class='line' id='LC919'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_payload_size</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span><span class="n">payload_size</span><span class="p">);</span></div><div class='line' id='LC920'><br></div><div class='line' id='LC921'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Note it would be more efficient to set all of the bits for all open</span></div><div class='line' id='LC922'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// pipes at once.  However, I thought it would make the calling code</span></div><div class='line' id='LC923'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// more simple to do it this way.</span></div><div class='line' id='LC924'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe_enable</span><span class="p">[</span><span class="n">child</span><span class="p">])));</span></div><div class='line' id='LC925'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC926'><span class="p">}</span></div><div class='line' id='LC927'><br></div><div class='line' id='LC928'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC929'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setAddressWidth</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">a_width</span><span class="p">){</span></div><div class='line' id='LC930'><br></div><div class='line' id='LC931'>	<span class="k">if</span><span class="p">(</span><span class="n">a_width</span> <span class="o">-=</span> <span class="mi">2</span><span class="p">){</span></div><div class='line' id='LC932'>		<span class="n">write_register</span><span class="p">(</span><span class="n">SETUP_AW</span><span class="p">,</span><span class="n">a_width</span><span class="o">%</span><span class="mi">4</span><span class="p">);</span></div><div class='line' id='LC933'>		<span class="n">addr_width</span> <span class="o">=</span> <span class="p">(</span><span class="n">a_width</span><span class="o">%</span><span class="mi">4</span><span class="p">)</span> <span class="o">+</span> <span class="mi">2</span><span class="p">;</span></div><div class='line' id='LC934'>	<span class="p">}</span></div><div class='line' id='LC935'><br></div><div class='line' id='LC936'><span class="p">}</span></div><div class='line' id='LC937'><br></div><div class='line' id='LC938'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC939'><br></div><div class='line' id='LC940'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">openReadingPipe</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">child</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="o">*</span><span class="n">address</span><span class="p">)</span></div><div class='line' id='LC941'><span class="p">{</span></div><div class='line' id='LC942'>&nbsp;&nbsp;<span class="c1">// If this is pipe 0, cache the address.  This is needed because</span></div><div class='line' id='LC943'>&nbsp;&nbsp;<span class="c1">// openWritingPipe() will overwrite the pipe 0 address, so</span></div><div class='line' id='LC944'>&nbsp;&nbsp;<span class="c1">// startListening() will have to restore it.</span></div><div class='line' id='LC945'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">child</span> <span class="o">==</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC946'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">memcpy</span><span class="p">(</span><span class="n">pipe0_reading_address</span><span class="p">,</span><span class="n">address</span><span class="p">,</span><span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC947'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC948'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">child</span> <span class="o">&lt;=</span> <span class="mi">6</span><span class="p">)</span></div><div class='line' id='LC949'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC950'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// For pipes 2-5, only write the LSB</span></div><div class='line' id='LC951'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">child</span> <span class="o">&lt;</span> <span class="mi">2</span> <span class="p">){</span></div><div class='line' id='LC952'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span> <span class="n">address</span><span class="p">,</span> <span class="n">addr_width</span><span class="p">);</span></div><div class='line' id='LC953'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC954'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span> <span class="n">address</span><span class="p">,</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC955'>	<span class="p">}</span></div><div class='line' id='LC956'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_payload_size</span><span class="p">[</span><span class="n">child</span><span class="p">]),</span><span class="n">payload_size</span><span class="p">);</span></div><div class='line' id='LC957'><br></div><div class='line' id='LC958'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Note it would be more efficient to set all of the bits for all open</span></div><div class='line' id='LC959'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// pipes at once.  However, I thought it would make the calling code</span></div><div class='line' id='LC960'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// more simple to do it this way.</span></div><div class='line' id='LC961'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe_enable</span><span class="p">[</span><span class="n">child</span><span class="p">])));</span></div><div class='line' id='LC962'><br></div><div class='line' id='LC963'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC964'><span class="p">}</span></div><div class='line' id='LC965'><br></div><div class='line' id='LC966'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC967'><br></div><div class='line' id='LC968'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">closeReadingPipe</span><span class="p">(</span> <span class="kt">uint8_t</span> <span class="n">pipe</span> <span class="p">)</span></div><div class='line' id='LC969'><span class="p">{</span></div><div class='line' id='LC970'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">EN_RXADDR</span><span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">pgm_read_byte</span><span class="p">(</span><span class="o">&amp;</span><span class="n">child_pipe_enable</span><span class="p">[</span><span class="n">pipe</span><span class="p">])));</span></div><div class='line' id='LC971'><span class="p">}</span></div><div class='line' id='LC972'><br></div><div class='line' id='LC973'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC974'><br></div><div class='line' id='LC975'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">toggle_features</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC976'><span class="p">{</span></div><div class='line' id='LC977'><br></div><div class='line' id='LC978'><span class="cp">  #if defined (__arm__) &amp;&amp; ! defined( CORE_TEENSY )</span></div><div class='line' id='LC979'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">ACTIVATE</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span> <span class="p">);</span></div><div class='line' id='LC980'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="mh">0x73</span> <span class="p">);</span></div><div class='line' id='LC981'><span class="cp">  #else</span></div><div class='line' id='LC982'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC983'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="n">ACTIVATE</span> <span class="p">);</span></div><div class='line' id='LC984'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span> <span class="mh">0x73</span> <span class="p">);</span></div><div class='line' id='LC985'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC986'><span class="cp">  #endif</span></div><div class='line' id='LC987'><span class="p">}</span></div><div class='line' id='LC988'><br></div><div class='line' id='LC989'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC990'><br></div><div class='line' id='LC991'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">enableDynamicPayloads</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC992'><span class="p">{</span></div><div class='line' id='LC993'>&nbsp;&nbsp;<span class="c1">// Enable dynamic payload throughout the system</span></div><div class='line' id='LC994'><br></div><div class='line' id='LC995'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">toggle_features</span><span class="p">();</span></div><div class='line' id='LC996'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_DPL</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC997'><br></div><div class='line' id='LC998'><br></div><div class='line' id='LC999'>&nbsp;&nbsp;<span class="n">IF_SERIAL_DEBUG</span><span class="p">(</span><span class="n">printf</span><span class="p">(</span><span class="s">&quot;FEATURE=%i</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)));</span></div><div class='line' id='LC1000'><br></div><div class='line' id='LC1001'>&nbsp;&nbsp;<span class="c1">// Enable dynamic payload on all pipes</span></div><div class='line' id='LC1002'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1003'>&nbsp;&nbsp;<span class="c1">// Not sure the use case of only having dynamic payload on certain</span></div><div class='line' id='LC1004'>&nbsp;&nbsp;<span class="c1">// pipes, so the library does not support it.</span></div><div class='line' id='LC1005'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">DYNPD</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">DYNPD</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P5</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P4</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P3</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P2</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P1</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P0</span><span class="p">));</span></div><div class='line' id='LC1006'><br></div><div class='line' id='LC1007'>&nbsp;&nbsp;<span class="n">dynamic_payloads_enabled</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC1008'><span class="p">}</span></div><div class='line' id='LC1009'><br></div><div class='line' id='LC1010'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1011'><br></div><div class='line' id='LC1012'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">enableAckPayload</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1013'><span class="p">{</span></div><div class='line' id='LC1014'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1015'>&nbsp;&nbsp;<span class="c1">// enable ack payload and dynamic payload features</span></div><div class='line' id='LC1016'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1017'><br></div><div class='line' id='LC1018'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">toggle_features</span><span class="p">();</span></div><div class='line' id='LC1019'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_ACK_PAY</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_DPL</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC1020'><br></div><div class='line' id='LC1021'>&nbsp;&nbsp;<span class="n">IF_SERIAL_DEBUG</span><span class="p">(</span><span class="n">printf</span><span class="p">(</span><span class="s">&quot;FEATURE=%i</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)));</span></div><div class='line' id='LC1022'><br></div><div class='line' id='LC1023'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1024'>&nbsp;&nbsp;<span class="c1">// Enable dynamic payload on pipes 0 &amp; 1</span></div><div class='line' id='LC1025'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1026'><br></div><div class='line' id='LC1027'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">DYNPD</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">DYNPD</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P1</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">DPL_P0</span><span class="p">));</span></div><div class='line' id='LC1028'>&nbsp;&nbsp;<span class="n">dynamic_payloads_enabled</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC1029'><span class="p">}</span></div><div class='line' id='LC1030'><br></div><div class='line' id='LC1031'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1032'><br></div><div class='line' id='LC1033'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">enableDynamicAck</span><span class="p">(</span><span class="kt">void</span><span class="p">){</span></div><div class='line' id='LC1034'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1035'>&nbsp;&nbsp;<span class="c1">// enable dynamic ack features</span></div><div class='line' id='LC1036'>&nbsp;&nbsp;<span class="c1">//</span></div><div class='line' id='LC1037'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">toggle_features</span><span class="p">();</span></div><div class='line' id='LC1038'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_DYN_ACK</span><span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC1039'><br></div><div class='line' id='LC1040'>&nbsp;&nbsp;<span class="n">IF_SERIAL_DEBUG</span><span class="p">(</span><span class="n">printf</span><span class="p">(</span><span class="s">&quot;FEATURE=%i</span><span class="se">\r\n</span><span class="s">&quot;</span><span class="p">,</span><span class="n">read_register</span><span class="p">(</span><span class="n">FEATURE</span><span class="p">)));</span></div><div class='line' id='LC1041'><br></div><div class='line' id='LC1042'><br></div><div class='line' id='LC1043'><span class="p">}</span></div><div class='line' id='LC1044'><br></div><div class='line' id='LC1045'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1046'><br></div><div class='line' id='LC1047'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">writeAckPayload</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pipe</span><span class="p">,</span> <span class="k">const</span> <span class="kt">void</span><span class="o">*</span> <span class="n">buf</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC1048'><span class="p">{</span></div><div class='line' id='LC1049'>&nbsp;&nbsp;<span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*</span> <span class="n">current</span> <span class="o">=</span> <span class="k">reinterpret_cast</span><span class="o">&lt;</span><span class="k">const</span> <span class="kt">uint8_t</span><span class="o">*&gt;</span><span class="p">(</span><span class="n">buf</span><span class="p">);</span></div><div class='line' id='LC1050'><br></div><div class='line' id='LC1051'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">data_len</span> <span class="o">=</span> <span class="n">min</span><span class="p">(</span><span class="n">len</span><span class="p">,</span><span class="mi">32</span><span class="p">);</span></div><div class='line' id='LC1052'><br></div><div class='line' id='LC1053'><span class="cp">  #if defined (__arm__) &amp;&amp; ! defined( CORE_TEENSY )</span></div><div class='line' id='LC1054'>	<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span> <span class="n">W_ACK_PAYLOAD</span> <span class="o">|</span> <span class="p">(</span> <span class="n">pipe</span> <span class="o">&amp;</span> <span class="n">B111</span> <span class="p">),</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC1055'>	<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span> <span class="o">&gt;</span> <span class="mi">1</span> <span class="p">){</span></div><div class='line' id='LC1056'>		<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">,</span> <span class="n">SPI_CONTINUE</span><span class="p">);</span></div><div class='line' id='LC1057'>	<span class="p">}</span></div><div class='line' id='LC1058'>	<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">csn_pin</span><span class="p">,</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">);</span></div><div class='line' id='LC1059'><br></div><div class='line' id='LC1060'><span class="cp">  #else</span></div><div class='line' id='LC1061'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC1062'>&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="n">W_ACK_PAYLOAD</span> <span class="o">|</span> <span class="p">(</span> <span class="n">pipe</span> <span class="o">&amp;</span> <span class="n">B111</span> <span class="p">)</span> <span class="p">);</span></div><div class='line' id='LC1063'><br></div><div class='line' id='LC1064'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span> <span class="n">data_len</span><span class="o">--</span> <span class="p">)</span></div><div class='line' id='LC1065'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SPI</span><span class="p">.</span><span class="n">transfer</span><span class="p">(</span><span class="o">*</span><span class="n">current</span><span class="o">++</span><span class="p">);</span></div><div class='line' id='LC1066'><br></div><div class='line' id='LC1067'>&nbsp;&nbsp;<span class="n">csn</span><span class="p">(</span><span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC1068'><br></div><div class='line' id='LC1069'><span class="cp">  #endif</span></div><div class='line' id='LC1070'><span class="p">}</span></div><div class='line' id='LC1071'><br></div><div class='line' id='LC1072'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1073'><br></div><div class='line' id='LC1074'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">isAckPayloadAvailable</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1075'><span class="p">{</span></div><div class='line' id='LC1076'>&nbsp;&nbsp;<span class="k">return</span> <span class="o">!</span> <span class="n">read_register</span><span class="p">(</span><span class="n">FIFO_STATUS</span><span class="p">)</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RX_EMPTY</span><span class="p">);</span></div><div class='line' id='LC1077'><span class="p">}</span></div><div class='line' id='LC1078'><br></div><div class='line' id='LC1079'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1080'><br></div><div class='line' id='LC1081'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">isPVariant</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1082'><span class="p">{</span></div><div class='line' id='LC1083'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">p_variant</span> <span class="p">;</span></div><div class='line' id='LC1084'><span class="p">}</span></div><div class='line' id='LC1085'><br></div><div class='line' id='LC1086'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1087'><br></div><div class='line' id='LC1088'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setAutoAck</span><span class="p">(</span><span class="kt">bool</span> <span class="n">enable</span><span class="p">)</span></div><div class='line' id='LC1089'><span class="p">{</span></div><div class='line' id='LC1090'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">enable</span> <span class="p">)</span></div><div class='line' id='LC1091'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">EN_AA</span><span class="p">,</span> <span class="n">B111111</span><span class="p">);</span></div><div class='line' id='LC1092'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1093'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="nf">write_register</span><span class="p">(</span><span class="n">EN_AA</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC1094'><span class="p">}</span></div><div class='line' id='LC1095'><br></div><div class='line' id='LC1096'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1097'><br></div><div class='line' id='LC1098'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setAutoAck</span><span class="p">(</span> <span class="kt">uint8_t</span> <span class="n">pipe</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">enable</span> <span class="p">)</span></div><div class='line' id='LC1099'><span class="p">{</span></div><div class='line' id='LC1100'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">pipe</span> <span class="o">&lt;=</span> <span class="mi">6</span> <span class="p">)</span></div><div class='line' id='LC1101'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1102'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">en_aa</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span> <span class="n">EN_AA</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1103'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">enable</span> <span class="p">)</span></div><div class='line' id='LC1104'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1105'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">en_aa</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">pipe</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1106'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1107'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1108'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1109'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">en_aa</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">pipe</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1110'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1111'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span> <span class="n">EN_AA</span><span class="p">,</span> <span class="n">en_aa</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1112'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1113'><span class="p">}</span></div><div class='line' id='LC1114'><br></div><div class='line' id='LC1115'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1116'><br></div><div class='line' id='LC1117'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">testCarrier</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1118'><span class="p">{</span></div><div class='line' id='LC1119'>&nbsp;&nbsp;<span class="k">return</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CD</span><span class="p">)</span> <span class="o">&amp;</span> <span class="mi">1</span> <span class="p">);</span></div><div class='line' id='LC1120'><span class="p">}</span></div><div class='line' id='LC1121'><br></div><div class='line' id='LC1122'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1123'><br></div><div class='line' id='LC1124'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">testRPD</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1125'><span class="p">{</span></div><div class='line' id='LC1126'>&nbsp;&nbsp;<span class="k">return</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">RPD</span><span class="p">)</span> <span class="o">&amp;</span> <span class="mi">1</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1127'><span class="p">}</span></div><div class='line' id='LC1128'><br></div><div class='line' id='LC1129'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1130'><br></div><div class='line' id='LC1131'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setPALevel</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">level</span><span class="p">)</span></div><div class='line' id='LC1132'><span class="p">{</span></div><div class='line' id='LC1133'><br></div><div class='line' id='LC1134'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">setup</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">)</span> <span class="o">&amp;</span> <span class="mi">0</span><span class="n">b11111000</span><span class="p">;</span></div><div class='line' id='LC1135'><br></div><div class='line' id='LC1136'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">level</span> <span class="o">&gt;</span> <span class="mi">3</span><span class="p">){</span>  						<span class="c1">// If invalid level, go to max PA</span></div><div class='line' id='LC1137'>	  <span class="n">level</span> <span class="o">=</span> <span class="p">(</span><span class="n">RF24_PA_MAX</span> <span class="o">&lt;&lt;</span> <span class="mi">1</span><span class="p">)</span> <span class="o">+</span> <span class="mi">1</span><span class="p">;</span>		<span class="c1">// +1 to support the SI24R1 chip extra bit</span></div><div class='line' id='LC1138'>&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC1139'>	  <span class="n">level</span> <span class="o">=</span> <span class="p">(</span><span class="n">level</span> <span class="o">&lt;&lt;</span> <span class="mi">1</span><span class="p">)</span> <span class="o">+</span> <span class="mi">1</span><span class="p">;</span>	 		<span class="c1">// Else set level as requested</span></div><div class='line' id='LC1140'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1141'><br></div><div class='line' id='LC1142'><br></div><div class='line' id='LC1143'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span> <span class="n">RF_SETUP</span><span class="p">,</span> <span class="n">setup</span> <span class="o">|=</span> <span class="n">level</span> <span class="p">)</span> <span class="p">;</span>	<span class="c1">// Write it to the chip</span></div><div class='line' id='LC1144'><span class="p">}</span></div><div class='line' id='LC1145'><br></div><div class='line' id='LC1146'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1147'><br></div><div class='line' id='LC1148'><span class="kt">uint8_t</span> <span class="n">RF24</span><span class="o">::</span><span class="n">getPALevel</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1149'><span class="p">{</span></div><div class='line' id='LC1150'><br></div><div class='line' id='LC1151'>&nbsp;&nbsp;<span class="k">return</span> <span class="p">(</span><span class="n">read_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">)</span> <span class="o">&amp;</span> <span class="p">(</span><span class="n">_BV</span><span class="p">(</span><span class="n">RF_PWR_LOW</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_PWR_HIGH</span><span class="p">)))</span> <span class="o">&gt;&gt;</span> <span class="mi">1</span> <span class="p">;</span></div><div class='line' id='LC1152'><span class="p">}</span></div><div class='line' id='LC1153'><br></div><div class='line' id='LC1154'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1155'><br></div><div class='line' id='LC1156'><span class="kt">bool</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setDataRate</span><span class="p">(</span><span class="n">rf24_datarate_e</span> <span class="n">speed</span><span class="p">)</span></div><div class='line' id='LC1157'><span class="p">{</span></div><div class='line' id='LC1158'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="n">result</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC1159'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">setup</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1160'><br></div><div class='line' id='LC1161'>&nbsp;&nbsp;<span class="c1">// HIGH and LOW &#39;00&#39; is 1Mbs - our default</span></div><div class='line' id='LC1162'>&nbsp;&nbsp;<span class="n">setup</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_LOW</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_HIGH</span><span class="p">))</span> <span class="p">;</span></div><div class='line' id='LC1163'>&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">speed</span> <span class="o">==</span> <span class="n">RF24_250KBPS</span> <span class="p">)</span></div><div class='line' id='LC1164'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1165'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0</span></div><div class='line' id='LC1166'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Making it &#39;10&#39;.</span></div><div class='line' id='LC1167'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">setup</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span> <span class="n">RF_DR_LOW</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1168'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1169'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1170'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1171'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1</span></div><div class='line' id='LC1172'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Making it &#39;01&#39;</span></div><div class='line' id='LC1173'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">speed</span> <span class="o">==</span> <span class="n">RF24_2MBPS</span> <span class="p">)</span></div><div class='line' id='LC1174'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1175'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">setup</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_HIGH</span><span class="p">);</span></div><div class='line' id='LC1176'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1177'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1178'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">,</span><span class="n">setup</span><span class="p">);</span></div><div class='line' id='LC1179'><br></div><div class='line' id='LC1180'>&nbsp;&nbsp;<span class="c1">// Verify our result</span></div><div class='line' id='LC1181'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">read_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">)</span> <span class="o">==</span> <span class="n">setup</span> <span class="p">)</span></div><div class='line' id='LC1182'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1183'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC1184'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1185'><br></div><div class='line' id='LC1186'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">result</span><span class="p">;</span></div><div class='line' id='LC1187'><span class="p">}</span></div><div class='line' id='LC1188'><br></div><div class='line' id='LC1189'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1190'><br></div><div class='line' id='LC1191'><span class="n">rf24_datarate_e</span> <span class="n">RF24</span><span class="o">::</span><span class="n">getDataRate</span><span class="p">(</span> <span class="kt">void</span> <span class="p">)</span></div><div class='line' id='LC1192'><span class="p">{</span></div><div class='line' id='LC1193'>&nbsp;&nbsp;<span class="n">rf24_datarate_e</span> <span class="n">result</span> <span class="p">;</span></div><div class='line' id='LC1194'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">dr</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">RF_SETUP</span><span class="p">)</span> <span class="o">&amp;</span> <span class="p">(</span><span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_LOW</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_HIGH</span><span class="p">));</span></div><div class='line' id='LC1195'><br></div><div class='line' id='LC1196'>&nbsp;&nbsp;<span class="c1">// switch uses RAM (evil!)</span></div><div class='line' id='LC1197'>&nbsp;&nbsp;<span class="c1">// Order matters in our case below</span></div><div class='line' id='LC1198'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">dr</span> <span class="o">==</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_LOW</span><span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC1199'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1200'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// &#39;10&#39; = 250KBPS</span></div><div class='line' id='LC1201'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">RF24_250KBPS</span> <span class="p">;</span></div><div class='line' id='LC1202'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1203'>&nbsp;&nbsp;<span class="k">else</span> <span class="k">if</span> <span class="p">(</span> <span class="n">dr</span> <span class="o">==</span> <span class="n">_BV</span><span class="p">(</span><span class="n">RF_DR_HIGH</span><span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC1204'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1205'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// &#39;01&#39; = 2MBPS</span></div><div class='line' id='LC1206'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">RF24_2MBPS</span> <span class="p">;</span></div><div class='line' id='LC1207'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1208'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1209'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1210'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// &#39;00&#39; = 1MBPS</span></div><div class='line' id='LC1211'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">RF24_1MBPS</span> <span class="p">;</span></div><div class='line' id='LC1212'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1213'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">result</span> <span class="p">;</span></div><div class='line' id='LC1214'><span class="p">}</span></div><div class='line' id='LC1215'><br></div><div class='line' id='LC1216'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1217'><br></div><div class='line' id='LC1218'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setCRCLength</span><span class="p">(</span><span class="n">rf24_crclength_e</span> <span class="n">length</span><span class="p">)</span></div><div class='line' id='LC1219'><span class="p">{</span></div><div class='line' id='LC1220'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">config</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="p">(</span> <span class="n">_BV</span><span class="p">(</span><span class="n">CRCO</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span><span class="p">))</span> <span class="p">;</span></div><div class='line' id='LC1221'><br></div><div class='line' id='LC1222'>&nbsp;&nbsp;<span class="c1">// switch uses RAM (evil!)</span></div><div class='line' id='LC1223'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">length</span> <span class="o">==</span> <span class="n">RF24_CRC_DISABLED</span> <span class="p">)</span></div><div class='line' id='LC1224'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1225'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Do nothing, we turned it off above.</span></div><div class='line' id='LC1226'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1227'>&nbsp;&nbsp;<span class="k">else</span> <span class="k">if</span> <span class="p">(</span> <span class="n">length</span> <span class="o">==</span> <span class="n">RF24_CRC_8</span> <span class="p">)</span></div><div class='line' id='LC1228'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1229'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">config</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span><span class="p">);</span></div><div class='line' id='LC1230'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1231'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1232'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1233'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">config</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span><span class="p">);</span></div><div class='line' id='LC1234'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">config</span> <span class="o">|=</span> <span class="n">_BV</span><span class="p">(</span> <span class="n">CRCO</span> <span class="p">);</span></div><div class='line' id='LC1235'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1236'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span> <span class="n">CONFIG</span><span class="p">,</span> <span class="n">config</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1237'><span class="p">}</span></div><div class='line' id='LC1238'><br></div><div class='line' id='LC1239'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1240'><br></div><div class='line' id='LC1241'><span class="n">rf24_crclength_e</span> <span class="n">RF24</span><span class="o">::</span><span class="n">getCRCLength</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC1242'><span class="p">{</span></div><div class='line' id='LC1243'>&nbsp;&nbsp;<span class="n">rf24_crclength_e</span> <span class="n">result</span> <span class="o">=</span> <span class="n">RF24_CRC_DISABLED</span><span class="p">;</span></div><div class='line' id='LC1244'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">config</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">&amp;</span> <span class="p">(</span> <span class="n">_BV</span><span class="p">(</span><span class="n">CRCO</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span><span class="p">))</span> <span class="p">;</span></div><div class='line' id='LC1245'><br></div><div class='line' id='LC1246'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">config</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span> <span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC1247'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC1248'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">config</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">CRCO</span><span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC1249'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">RF24_CRC_16</span><span class="p">;</span></div><div class='line' id='LC1250'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC1251'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">result</span> <span class="o">=</span> <span class="n">RF24_CRC_8</span><span class="p">;</span></div><div class='line' id='LC1252'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC1253'><br></div><div class='line' id='LC1254'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">result</span><span class="p">;</span></div><div class='line' id='LC1255'><span class="p">}</span></div><div class='line' id='LC1256'><br></div><div class='line' id='LC1257'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1258'><br></div><div class='line' id='LC1259'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">disableCRC</span><span class="p">(</span> <span class="kt">void</span> <span class="p">)</span></div><div class='line' id='LC1260'><span class="p">{</span></div><div class='line' id='LC1261'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">disable</span> <span class="o">=</span> <span class="n">read_register</span><span class="p">(</span><span class="n">CONFIG</span><span class="p">)</span> <span class="o">&amp;</span> <span class="o">~</span><span class="n">_BV</span><span class="p">(</span><span class="n">EN_CRC</span><span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1262'>&nbsp;&nbsp;<span class="n">write_register</span><span class="p">(</span> <span class="n">CONFIG</span><span class="p">,</span> <span class="n">disable</span> <span class="p">)</span> <span class="p">;</span></div><div class='line' id='LC1263'><span class="p">}</span></div><div class='line' id='LC1264'><br></div><div class='line' id='LC1265'><span class="cm">/****************************************************************************/</span></div><div class='line' id='LC1266'><span class="kt">void</span> <span class="n">RF24</span><span class="o">::</span><span class="n">setRetries</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">delay</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">count</span><span class="p">)</span></div><div class='line' id='LC1267'><span class="p">{</span></div><div class='line' id='LC1268'>&nbsp;<span class="n">write_register</span><span class="p">(</span><span class="n">SETUP_RETR</span><span class="p">,(</span><span class="n">delay</span><span class="o">&amp;</span><span class="mh">0xf</span><span class="p">)</span><span class="o">&lt;&lt;</span><span class="n">ARD</span> <span class="o">|</span> <span class="p">(</span><span class="n">count</span><span class="o">&amp;</span><span class="mh">0xf</span><span class="p">)</span><span class="o">&lt;&lt;</span><span class="n">ARC</span><span class="p">);</span></div><div class='line' id='LC1269'><span class="p">}</span></div><div class='line' id='LC1270'><br></div><div class='line' id='LC1271'><br></div><div class='line' id='LC1272'><span class="c1">//ATTiny support code pulled in from https://github.com/jscrane/RF24</span></div><div class='line' id='LC1273'><br></div><div class='line' id='LC1274'><span class="cp">#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)</span></div><div class='line' id='LC1275'><span class="c1">// see http://gammon.com.au/spi</span></div><div class='line' id='LC1276'><span class="cp">#	define DI   0  </span><span class="c1">// D0, pin 5  Data In</span></div><div class='line' id='LC1277'><span class="cp">#	define DO   1  </span><span class="c1">// D1, pin 6  Data Out (this is *not* MOSI)</span></div><div class='line' id='LC1278'><span class="cp">#	define USCK 2  </span><span class="c1">// D2, pin 7  Universal Serial Interface clock</span></div><div class='line' id='LC1279'><span class="cp">#	define SS   3  </span><span class="c1">// D3, pin 2  Slave Select</span></div><div class='line' id='LC1280'><span class="cp">#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)</span></div><div class='line' id='LC1281'><span class="c1">// these depend on the core used (check pins_arduino.h)</span></div><div class='line' id='LC1282'><span class="c1">// this is for jeelabs&#39; one (based on google-code core)</span></div><div class='line' id='LC1283'><span class="cp">#	define DI   4   </span><span class="c1">// PA6</span></div><div class='line' id='LC1284'><span class="cp">#	define DO   5   </span><span class="c1">// PA5</span></div><div class='line' id='LC1285'><span class="cp">#	define USCK 6   </span><span class="c1">// PA4</span></div><div class='line' id='LC1286'><span class="cp">#	define SS   3   </span><span class="c1">// PA7</span></div><div class='line' id='LC1287'><span class="cp">#endif</span></div><div class='line' id='LC1288'><br></div><div class='line' id='LC1289'><span class="cp">#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)</span></div><div class='line' id='LC1290'><br></div><div class='line' id='LC1291'><span class="kt">void</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">begin</span><span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC1292'><br></div><div class='line' id='LC1293'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">SS</span><span class="p">,</span> <span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC1294'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">USCK</span><span class="p">,</span> <span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC1295'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">DO</span><span class="p">,</span> <span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC1296'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">SS</span><span class="p">,</span> <span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC1297'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">DI</span><span class="p">,</span> <span class="n">INPUT</span><span class="p">);</span></div><div class='line' id='LC1298'>&nbsp;&nbsp;<span class="n">USICR</span> <span class="o">=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USIWM0</span><span class="p">);</span></div><div class='line' id='LC1299'><br></div><div class='line' id='LC1300'><span class="p">}</span></div><div class='line' id='LC1301'><br></div><div class='line' id='LC1302'><span class="n">byte</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">transfer</span><span class="p">(</span><span class="n">byte</span> <span class="n">b</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC1303'><br></div><div class='line' id='LC1304'>&nbsp;&nbsp;<span class="n">USIDR</span> <span class="o">=</span> <span class="n">b</span><span class="p">;</span></div><div class='line' id='LC1305'>&nbsp;&nbsp;<span class="n">USISR</span> <span class="o">=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USIOIF</span><span class="p">);</span></div><div class='line' id='LC1306'>&nbsp;&nbsp;<span class="k">do</span></div><div class='line' id='LC1307'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">USICR</span> <span class="o">=</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USIWM0</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USICS1</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USICLK</span><span class="p">)</span> <span class="o">|</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USITC</span><span class="p">);</span></div><div class='line' id='LC1308'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">((</span><span class="n">USISR</span> <span class="o">&amp;</span> <span class="n">_BV</span><span class="p">(</span><span class="n">USIOIF</span><span class="p">))</span> <span class="o">==</span> <span class="mi">0</span><span class="p">);</span></div><div class='line' id='LC1309'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">USIDR</span><span class="p">;</span></div><div class='line' id='LC1310'><br></div><div class='line' id='LC1311'><span class="p">}</span></div><div class='line' id='LC1312'><br></div><div class='line' id='LC1313'><span class="kt">void</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">end</span><span class="p">()</span> <span class="p">{}</span></div><div class='line' id='LC1314'><span class="kt">void</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">setDataMode</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">mode</span><span class="p">){}</span></div><div class='line' id='LC1315'><span class="kt">void</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">setBitOrder</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">bitOrder</span><span class="p">){}</span></div><div class='line' id='LC1316'><span class="kt">void</span> <span class="n">SPIClass</span><span class="o">::</span><span class="n">setClockDivider</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">rate</span><span class="p">){}</span></div><div class='line' id='LC1317'><br></div><div class='line' id='LC1318'><br></div><div class='line' id='LC1319'><span class="cp">#endif</span></div></pre></div></td>
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
      <li>&copy; 2014 <span title="0.04193s from github-fe124-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
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

