class CargoGrid
{
	EntityAI m_Entity;
	ItemsContainer m_ItemsContainer;
	ref array<int> m_ShowedItems;
	ref array<GridContainer> m_Rows;
	Container m_Parent;
	
	void SetParent( Container parent )
	{
		m_Parent = parent;
	}
	void CargoGrid( EntityAI entity, ItemsContainer items_container )
	{
		m_Entity = entity;
		m_ItemsContainer = items_container;
		m_ShowedItems = new array<int>;
		m_Rows =  new array<GridContainer>;
		
		RecomputeGridHeight();
	}
	
	void RecomputeGridHeight()
	{
		for( int i = 0; i < m_Rows.Count(); i++ )
		{
			delete m_Rows.Get( i ).GetMainPanel();
			m_ItemsContainer.Remove( m_Rows.Get( i ) );
		}
		m_Rows.Clear();
		
			//START - Init grid rows
			Print( m_ItemsContainer.GetItemCount() );
			
			#ifdef PLATFORM_XBOX
			int cargo_height = ((m_ItemsContainer.GetItemCount() / 4)*2) + 2;
			#else
			int cargo_height = 	m_Entity.GetInventory().GetCargo().GetHeight();
			#endif

			for ( int j = 0; j < cargo_height; j++ )
			{
				GridContainer row = new GridContainer( m_ItemsContainer );
				row.SetNumber( j );
				row.SetEntity( m_Entity );
				row.SetWidth( m_Entity.GetInventory().GetCargo().GetWidth() );
				m_ItemsContainer.Insert( row );
				m_Rows.Insert( row );
			}
		
		m_ItemsContainer.Refresh();
		//END - Init grid rows
		
		
	}
	
	void Remove()
	{
		delete m_ItemsContainer.GetMainPanel();
		for( int i = 0; i < m_Rows.Count(); i++ )
		{
			delete m_Rows.Get( i ).GetMainPanel();
		}
		m_Rows.Clear();
		delete m_ItemsContainer;
	}
	
	void TransferItemToVicinity()
	{
		Man player = GetGame().GetPlayer();
		EntityAI entity = GetFocusedItem();
		if( entity && player.CanDropEntity( entity ) )
		{
			player.PredictiveDropEntity( entity );
		}
	}
	
	void TransferItem()
	{
		EntityAI entity = GetFocusedItem();
		if( entity )
		{
			GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.CARGO, entity );
		}
	}
	
	void EquipItem()
	{
		ItemBase entity = ItemBase.Cast( GetFocusedItem() );
		if( entity && !entity.IsInherited( Magazine ) )
		{
			if( entity.HasQuantity() )
			{
				entity.OnRightClick();
				Icon icon = m_ItemsContainer.GetIcon( entity.GetID() );
				
				if ( icon )
				{
					icon.RefreshQuantity();
				}
			}
			else
			{
				GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.ATTACHMENT, entity );
			}
				
		}
	}
	
	EntityAI GetFocusedItem()
	{
		GridContainer focused_row = m_Rows.Get( m_FocusedRowNumber );
		int focused_column = focused_row.GetFocusedColumn();
		return m_Entity.GetInventory().GetCargo().FindEntityInCargoOn( m_FocusedRowNumber, focused_column );
	}

	protected int m_FocusedRowNumber;

	int GetFocusedRowNumber()
	{
		return m_FocusedRowNumber;
	}

	int GetFocusedColumnNumber()
	{
		GridContainer focused_row = m_Rows.Get( m_FocusedRowNumber );
		return focused_row.GetFocusedColumn();
	}
	void MoveGridCursor( int direction )
	{
		GridContainer focused_row = m_Rows.Get( m_FocusedRowNumber );
		int focused_column = focused_row.GetFocusedColumn();
		focused_row.UnfocusAll();
		
		int width = 1;
		int height = 1;
		
		focused_row.GetIconSize(m_FocusedRowNumber, focused_column, width, height);
		
		
		if( direction == Direction.UP )
		{
			m_FocusedRowNumber--;
			
			if( m_FocusedRowNumber < 0 )
			{
				m_FocusedRowNumber  = ( m_Rows.Count() - 1 ) ;
				Container cnt = Container.Cast( m_ItemsContainer.GetParent().GetParent().GetParent() );
				cnt.SetPreviousActive();
				return;
			}			
		}
		else if( direction == Direction.DOWN )
		{
			m_FocusedRowNumber += height;
			
			if( m_FocusedRowNumber >= m_Rows.Count() )
			{
				m_FocusedRowNumber  = 0 ;
				cnt = Container.Cast( m_ItemsContainer.GetParent().GetParent().GetParent() );
				cnt.SetNextActive();
				return;
			}
		}
		else if( direction == Direction.RIGHT )
		{
			focused_column += width;
			
			if( focused_column >= focused_row.GetWidth() )
			{
				focused_column = 0 ;
			}
		}
		else if( direction == Direction.LEFT )
		{
			focused_column--;
			
			if( focused_column < 0 )
			{
				focused_column = ( focused_row.GetWidth() - 1 );
			}			
		}
		
		int icon_pos_x;
		int icon_pos_y;
		if ( focused_row.GetIconPosition(m_FocusedRowNumber, focused_column, icon_pos_x, icon_pos_y) )
		{
			focused_column = icon_pos_x;
			m_FocusedRowNumber = icon_pos_y;
		}
		
		GridContainer focused_cont_row = m_Rows.Get( m_FocusedRowNumber );
		focused_cont_row.SetFocus( focused_column );
	}

	void SetDefaultFocus()
	{
		Unfocus();
		GridContainer focused_row = m_Rows.Get( m_FocusedRowNumber );
		focused_row.SetFocus( 0 );
	}

	void Unfocus()
	{
		Entity focused_item_old = GetFocusedItem();
		if ( focused_item_old )
		{
			Icon icon_old = m_ItemsContainer.GetIcon( focused_item_old.GetID() );
			
			if ( icon_old )
			{
				icon_old.SetActive( false );
			} 
		}
		
		GridContainer focused_row = m_Rows.Get( m_FocusedRowNumber );
		focused_row.UnfocusAll();
		m_FocusedRowNumber = 0;
	}

	void UpdateInterval()
	{
		if( m_Entity )
		{
			ref array<int> showed_items = new array<int>;
			
			//START - Add new item Icons
				for ( int j = 0; j < m_Entity.GetInventory().GetCargo().GetItemCount(); j++ )
				{
					EntityAI item = InitIcon( j );
					showed_items.Insert( item.GetID() );
				}
			//END - Add new Icons

			m_ItemsContainer.UpdateItemsTemperature();

			//START - Remove removed item Icons
				for ( int i = 0; i < m_ShowedItems.Count(); i++ )
				{
					int showed_item = m_ShowedItems.Get( i );
					if( showed_items.Find( showed_item ) == INDEX_NOT_FOUND )
					{
						m_ItemsContainer.RemoveItem( showed_item );
						ItemManager.GetInstance().HideTooltip();
						#ifdef PLATFORM_XBOX
						RecomputeGridHeight();
						m_Parent.Refresh();
						m_ItemsContainer.RecomputeItemPositions();
						#endif
					}
				}
			//END - Remove removed item Icons

			m_ShowedItems = showed_items;
		}
	}

	EntityAI InitIcon( int index )
	{
		EntityAI item = m_Entity.GetInventory().GetCargo().GetItem( index );
		if( !m_ItemsContainer.ContainsEntity( item ) )
		{
			#ifdef PLATFORM_XBOX
			RecomputeGridHeight();
			m_Parent.Refresh();
			( Container.Cast( m_Parent.m_Parent.m_Parent ) ).UpdateBodySpacers();
			#endif
			int pos_x, pos_y, size_x, size_y;
			m_Entity.GetInventory().GetCargo().GetItemSize( index, size_x, size_y );
			m_Entity.GetInventory().GetCargo().GetItemPos( index, pos_x, pos_y );

			Icon icon = new Icon( m_ItemsContainer );
			icon.Init( item );
			#ifdef PLATFORM_XBOX
			icon.SetSize( 2, 2 );
			icon.SetPos( (m_ItemsContainer.GetItemCount() % 4)*2, (m_ItemsContainer.GetItemCount() / 4)*2 );
			icon.m_posX = (m_ItemsContainer.GetItemCount() % 4)*2;
			icon.m_posY = (m_ItemsContainer.GetItemCount() / 4)*2;
			icon.SetCargoPos( index );
			#else
			icon.SetSize( size_x, size_y );
			icon.SetPos( pos_x, pos_y );
			icon.m_posX = pos_x;
			icon.m_posY = pos_y;
			#endif
			m_ItemsContainer.AddItem( icon );
		}

		return item;
	}
}
