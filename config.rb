require 'slim'

set :site_title, "IIC2333 - SO y Redes"
#set :site_url, "http://www.domain.com"
#set :site_description, "Meta description."
#set :site_keywords, "keyword-one, keyword-two"

# Page options, layouts, aliases and proxies
# ============
set :relative_links, true
activate :relative_assets
set :relative_links, true


# Assets
# ======
set :css_dir,    "css"
set :js_dir,     "js"
set :images_dir, "images"


# Per-page layout changes
# -----------------------
# With no layout
page '/*.xml',  layout: false
page '/*.json', layout: false
page '/*.txt',  layout: false

# With alternative layout
# page '/path/to/file.html', layout: :otherlayout

# Proxy pages (http://middlemanapp.com/basics/dynamic-pages/)
# proxy '/this-page-has-no-template.html', '/template-file.html', locals: {
#  which_fake_page: 'Rendering a fake page with a local variable' }



# Helpers
# =======

# Reload the browser automatically whenever files change
# configure :development do
#   activate :livereload
# end

# Methods defined in the helpers block are available in templates
# helpers do
#   def some_helper
#     'Helping'
#   end
# end


# Build-specific configuration
# ============================
configure :build do
  # activate :minify_css
  # activate :minify_javascript
  # activate :minify_html

  # activate :asset_hash
end
