class UICargoGrid
{
	protected const int ROWS_NUMBER_XBOX = 5;
	protected EntityAI m_Entity;
	protected ItemsContainer m_ItemsContainer;
	protected ref array<int> m_ShowedItems;
	protected ref array<GridContainer> m_Rows;
	protected Container m_Parent;
	protected bool m_SetDefaultFocusAfterInitIcon;
	protected bool m_RefreshItemPositions;
	
	void SetParent( Container parent )
	{
		m_Parent = parent;
		int capacity = m_Entity.GetInventory().GetCargo().GetHeight() * m_Entity.GetInventory().GetCargo().GetWidth();
		TextWidget tw = m_Parent.GetMainPanel().FindAnyWidget("CargoCount");
		#ifdef PLATFORM_XBOX
			if( tw )
				tw.Show( true );
		#endif
		if(tw)
		tw.SetText("0/" + capacity);
	}
	void UICargoGrid( EntityAI entity, ItemsContainer items_container )
	{
		m_Entity = entity;
		m_ItemsContainer = items_container;
		m_ShowedItems = new array<int>;
		m_Rows =  new array<GridContainer>;
		RecomputeGridHeight();
	}
	
	void SetActive( bool active )
	{
		m_ItemsContainer.SetActive( active );
		if( active )
		{
			SetDefaultFocus();
		}
	}
	
	bool IsActive()
	{
		return m_ItemsContainer.IsActive();
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
			
			#ifdef PLATFORM_XBOX
			int cargo_height = ( ( m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX ) * 2 ) + 2;
			if( m_ItemsContainer.GetItemCount() % ROWS_NUMBER_XBOX == 0 )
			{
				cargo_height = ( ( m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX ) * 2 );
			}
			if( m_ItemsContainer.GetItemCount() == 0 )
			{
				cargo_height = 2;
			}
			#else
			int cargo_height = 	m_Entity.GetInventory().GetCargo().GetHeight();
			#endif

			for ( int j = 0; j < cargo_height; j++ )
			{
				GridContainer row = new GridContainer( m_ItemsContainer );
				row.SetNumber( j    );
				row.SetEntity( m_Entity );
				row.SetWidth( m_Entity.GetInventory().GetCargo().GetWidth() );
				m_ItemsContainer.Insert( row );
				m_Rows.Insert( row );
			}
		
		//m_ItemsContainer.Refresh();
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
		Icon icon = GetFocusedItem();
		if( icon )
		{
			EntityAI entity = EntityAI.Cast( icon.GetObject() );
			if( entity && player.CanDropEntity( entity ) )
			{
				player.PredictiveDropEntity( entity );
			}
		}
		m_ReactivateCursor = true;
	}
	
	void TransferItem()
	{
		EntityAI entity = EntityAI.Cast( GetFocusedItem().GetObject() );
		if( entity )
		{
			GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.CARGO, entity );
		}
		m_ReactivateCursor = true;
	}
	
	bool m_ReactivateCursor;
	
	void PrepareCursorReactivation()
	{
		m_ReactivateCursor = true;
	}
	
	void EquipItem()
	{
		ItemBase entity = ItemBase.Cast( GetFocusedItem().GetObject() );
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
	
	Icon GetFocusedItem()
	{
		if( m_ItemsContainer.GetItemCount() <= m_FocusedItemPosition )
		{
			return NULL;
		}
		else
		{
			return m_ItemsContainer.GetIconByIndex( m_FocusedItemPosition );
		}
	}
	
	int m_FocusedItemPosition = 0;
	void MoveGridCursor( int direction )
	{
		if( !ItemManager.GetInstance().IsMicromanagmentMode() )
		{
			Container cnt;
			
			Icon icon = m_ItemsContainer.GetIconByIndex( m_FocusedItemPosition );
			if( icon == NULL )
			{
				return;
			}
			icon.SetActive( false );
			
			int focused_row = m_FocusedItemPosition / ROWS_NUMBER_XBOX;
			int max_rows = m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX + 1;
			if( m_ItemsContainer.GetItemCount() % ROWS_NUMBER_XBOX == 0 )
			{
				max_rows = m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX;
			}
			int row_min = focused_row * ROWS_NUMBER_XBOX;
			int row_max = row_min + ROWS_NUMBER_XBOX - 1;
			
			if(row_max >= m_ItemsContainer.GetItemCount() )
			{
				row_max = m_ItemsContainer.GetItemCount() - 1;
			}
			
			if( direction == Direction.UP )
			{
				m_FocusedItemPosition -= ROWS_NUMBER_XBOX;
				if( m_FocusedItemPosition < 0 )
				{
					m_FocusedItemPosition = m_ItemsContainer.GetItemCount() - 1;
					cnt = Container.Cast( m_ItemsContainer.GetParent().GetParent().GetParent() );
					if( cnt )
					{
						cnt.SetPreviousActive();
					}
					else
					{
						cnt = Container.Cast( m_ItemsContainer.GetParent() );
						cnt.SetPreviousActive();
					}
					return;
				}
			}
			else if( direction == Direction.DOWN )
			{
				m_FocusedItemPosition += ROWS_NUMBER_XBOX;
				if( m_FocusedItemPosition > m_ItemsContainer.GetItemCount() - 1 )
				{
					if( focused_row < max_rows - 1 )
					{
						m_FocusedItemPosition = m_ItemsContainer.GetItemCount() - 1;
					}
					else
					{
						cnt = Container.Cast( m_ItemsContainer.GetParent().GetParent().GetParent() );
						if( cnt )
						{
							cnt.SetNextActive();
						}
						else
						{
							cnt = Container.Cast( m_ItemsContainer.GetParent() );
							cnt.SetNextActive();
						}
						m_FocusedItemPosition = 0;
						return;
					}
				}
			}
			else if( direction == Direction.RIGHT )
			{
				m_FocusedItemPosition++;
				if( m_FocusedItemPosition > row_max  )
				{
					m_FocusedItemPosition = row_min;
				}
			}
			else if( direction == Direction.LEFT )
			{
				m_FocusedItemPosition--;
				if( m_FocusedItemPosition < row_min  )
				{
					m_FocusedItemPosition = row_max;
				}
			}
			
			icon = m_ItemsContainer.GetIconByIndex( m_FocusedItemPosition );
			if( icon )
			{
				icon.SetActive( true );
			}
		}
	}
	
	void SetDefaultFocus( bool while_micromanagment_mode = false )
	{
		if( !while_micromanagment_mode && ItemManager.GetInstance().IsMicromanagmentMode() )
		{
			return;
		}
		Unfocus();
		if( m_ItemsContainer.GetItemCount() )
		{
			Icon icon = m_ItemsContainer.GetIconByIndex( 0 );
			icon.SetActive( true );
		}
	}

	void Unfocus()
	{
		Icon focused_item_old = GetFocusedItem();
		if(!focused_item_old)
		{
			return;
		}
		focused_item_old.SetActive( false );
		m_FocusedItemPosition = 0;
	}
	
	void SetDefaultFocusAfterInitIcon()
	{
		m_SetDefaultFocusAfterInitIcon = true;
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
			#ifdef PLATFORM_XBOX
				if( m_RefreshItemPositions )
				{
						RecomputeGridHeight();
						if(m_Parent)
							m_Parent.Refresh();
						m_ItemsContainer.RecomputeItemPositions();
						if(Container.Cast( m_Parent.m_Parent.m_Parent ) )
							( Container.Cast( m_Parent.m_Parent.m_Parent ) ).UpdateBodySpacers();
						else
							HandsContainer.Cast( m_Parent ).RefreshHands();
					
					m_RefreshItemPositions = false;
				}
			#endif
			m_ItemsContainer.UpdateItemsTemperature();

			//START - Remove removed item Icons
			for ( int i = 0; i < m_ShowedItems.Count(); i++ )
			{
				int showed_item = m_ShowedItems.Get( i );
				if( showed_items.Find( showed_item ) == INDEX_NOT_FOUND )
				{
					int size_x, size_y;
					Icon iconn = m_ItemsContainer.GetIcon( showed_item );
					if( iconn )
					{
						EntityAI ent = iconn.GetObject();
						if( ent )
						{
							GetGame().GetInventoryItemSize( ent, size_x, size_y );
							int capacity = m_Entity.GetInventory().GetCargo().GetHeight() * m_Entity.GetInventory().GetCargo().GetWidth();
							occupied_cargo = occupied_cargo - size_x * size_y;
							
							TextWidget tw = m_Parent.GetMainPanel().FindAnyWidget("CargoCount");
							string cargo_count = occupied_cargo.ToString() + "/" + capacity;
							if(tw)
								tw.SetText( cargo_count );
							
							m_ItemsContainer.RemoveItem( showed_item );
							ItemManager.GetInstance().HideTooltip();
							#ifdef PLATFORM_XBOX
								RecomputeGridHeight();
								m_Parent.Refresh();
								m_ItemsContainer.RecomputeItemPositions();
								
								if( !ItemManager.GetInstance().IsMicromanagmentMode() && m_ReactivateCursor && m_ItemsContainer.GetItemCount() > 0 )
								{
									Icon icon = m_ItemsContainer.GetIconByIndex( m_FocusedItemPosition );
									if( icon )
									{
										icon.SetActive( true );
										m_ReactivateCursor = false;
									}
								}
								
								Container cnt = Container.Cast( m_ItemsContainer.GetParent().GetParent().GetParent() );
								if( cnt )
								{
									cnt.UpdateBodySpacers();
								}
								else
								{
									cnt = Container.Cast( m_ItemsContainer.GetParent() );
									cnt.UpdateBodySpacers();
								}
							#endif
						}
						else
						{
							m_ItemsContainer.RemoveItem( iconn );
							#ifdef PLATFORM_XBOX
								RecomputeGridHeight();
								if(m_Parent)
									m_Parent.Refresh();
								m_ItemsContainer.RecomputeItemPositions();
								if(Container.Cast( m_Parent.m_Parent.m_Parent ) )
									( Container.Cast( m_Parent.m_Parent.m_Parent ) ).UpdateBodySpacers();
								else
									HandsContainer.Cast( m_Parent ).RefreshHands();
							#endif
							delete iconn;
						}
					}
				}
			}
			//END - Remove removed item Icons

			m_ShowedItems = showed_items;
		}
	}
	
	int occupied_cargo;

	EntityAI InitIcon( int index )
	{
		EntityAI item = m_Entity.GetInventory().GetCargo().GetItem( index );
		if( !m_ItemsContainer.ContainsEntity( item ) )
		{
			int pos_x, pos_y, size_x, size_y;
			m_Entity.GetInventory().GetCargo().GetItemSize( index, size_x, size_y );
			m_Entity.GetInventory().GetCargo().GetItemRowCol( index, pos_y, pos_x );
			int capacity = m_Entity.GetInventory().GetCargo().GetHeight() * m_Entity.GetInventory().GetCargo().GetWidth();
			occupied_cargo = occupied_cargo + size_x * size_y;
			
			TextWidget tw = m_Parent.GetMainPanel().FindAnyWidget("CargoCount");
			string cargo_count = occupied_cargo.ToString() + "/" + capacity;
			if(tw)
				tw.SetText( cargo_count );

			Icon icon = new Icon( m_ItemsContainer );
			icon.Init( item );
			#ifdef PLATFORM_XBOX
				icon.SetSize( 2, 2 );
				icon.SetPos( (m_ItemsContainer.GetItemCount() % ROWS_NUMBER_XBOX)*2, (m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX)*2 );
				icon.m_posX = (m_ItemsContainer.GetItemCount() % ROWS_NUMBER_XBOX)*2;
				icon.m_posY = (m_ItemsContainer.GetItemCount() / ROWS_NUMBER_XBOX)*2;
				icon.SetCargoPos( index );
			#else
				icon.SetSize( size_x, size_y );
				icon.SetPos( pos_x, pos_y );
				icon.m_posX = pos_x;
				icon.m_posY = pos_y;
			#endif
			m_ItemsContainer.AddItem( icon );
			
			#ifdef PLATFORM_XBOX
			m_RefreshItemPositions = true;
			#endif
			
			if( m_SetDefaultFocusAfterInitIcon )
			{
				SetDefaultFocus();
				m_SetDefaultFocusAfterInitIcon = false;
			}
		}

		return item;
	}
}
